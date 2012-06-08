/*
 * share_secret.c
 *
 *  Created on: Jun 5, 2012
 *      Author: luckpizza
 */

#include <stdlib.h>
#include <stdio.h>
#include "status_definitions.h"
#include "memory_utils.h"
#include "debug.h"
#include "bitmap.h"
#include "share_secret_utils.h"
#include "bite_wise.h"
#include "mod251_operations.h"

typedef struct img_with_state{
	simple_8bits_BMP_t * img;
	unsigned char * current_bytes;
	int i;
	int j;
	int k;
}img_with_state_t;

typedef struct row{
	unsigned char * bytes;
	unsigned char b;
	int index;
}row_t;
/**
 * creates a new img_with_state from a iamgine and the k magic number
 */
img_with_state_t *
new_one_step_in_img(simple_8bits_BMP_t * img,int k)
{
	img_with_state_t * rta = my_malloc(sizeof(img_with_state_t));
	if(img == NULL)
	{
		error("Trying to initializate state of a NULL img");
		return NULL;
	}

//	rta->current_bytes = my_malloc(k * sizeof(unsigned char));
	rta->current_bytes =NULL;
	rta->i = 0;
	rta->j = 0;
	rta->k = k;
	rta->img = img;

	return rta;
}

/**
 * makes imgs created by @see new_one_step_in_img go one iteration fordware
 * saving the modifications to the image.
 */
int
one_step_in_img(img_with_state_t * img)
{
	int idx = 0;
	int i =0, j = 0 ;

	if(img == NULL || img->img ==NULL || img->k ==0 ){
		error("trying to make one step to a wrong file!");
	}
	if(img->i ==-1)
	{
		info("we are done with this img! stop calling this function!!");
		return DONE;
	}
	if(img->current_bytes != NULL)
	{
		while(idx < img->k)
		{
			if(img->j < img->img->dib_header->width)
			{
				img->img->img[img->i][img->j] = img->current_bytes[idx];
				++img->j;
			}else if(img->i < (img->img->dib_header->height -1))
			{
				++img->i;
				img->j = 0;
				img->img->img[img->i][img->j] = img->current_bytes[idx];
			}else
			{
				error(" one_step_in_img error  ... trying to modify more height than permited");
				return ERROR;
			}
			++idx;
		}
	}
	if(img->current_bytes == NULL)
	{
		debug("one_step_in_img first call of this function");
		img->current_bytes = my_malloc(img->k * sizeof(unsigned char));

	}
	idx = 0;
	j = img->j ;
	i = img->i;
	while(idx < img->k)
	{
		if(j < img->img->dib_header->width)
		{
			 img->current_bytes[idx] = img->img->img[i][j];
			++j;
		}else if(i < (img->img->dib_header->height -1))
		{
			++i;
			j = 0;
			 img->current_bytes[idx] = img->img->img[i][j];
		}else
		{
			debug(" one_step_in_img : We reach the end of the image");
			img->i = -1; //Invalidate the image so it can't enter to this function any more!
			return DONE;
		}
		++idx;
	}
	return OK;
}

int
one_step_in_imgs(img_with_state_t ** img, int n)
{
	int i = 0;
	int status = 0;
	for(i = 0 ; i < n ; ++i)
	{
		status =one_step_in_img(img[i]);
	}
	return status;
}

void
swap_rows( row_t * a, row_t * b)
{
	row_t tmp;
	tmp.b = a->b;
	tmp.bytes = a->bytes;
	tmp.index = a->index;
	a->b = b->b;
	a->bytes = b->bytes;
	a->index = b->index;
	b->b = tmp.b;
	b->bytes = tmp.bytes;
	b->index = tmp.index;
//
//	a = b;
//	b = tmp;
}
void
swap_bytes(unsigned char ** a, unsigned char ** b)
{
	unsigned char ** tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void
swap_char( unsigned char *a, unsigned char *b)
{
	unsigned char * tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void
x_mul_bytes(unsigned char x, unsigned char * bytes, int k)
{
	int i;
	for ( i = 0; i < k; ++i) {
		bytes[i] = mul(bytes[i], x);
	}
}

void
x_mul_row(unsigned char x, row_t * row, int k)
{
	x_mul_bytes(x, row->bytes, k );
	row->b = mul(row->b, x);

}

void
row_sub_row(row_t * a, row_t * b, int k)
{
	int i;
	for ( i = 0; i < k; ++i) {
		a->bytes[i] = sub(a->bytes[i], b->bytes[i]);
	}
	a->b = sub(a->b , b->b);

}

int
calculate_secret_bytes(unsigned char **bytes,unsigned char * bs, unsigned char * recover_bytes,int k )
{
	int i, j;
	unsigned char check1 = 0;
	unsigned char check2 = 0;
	row_t * rows = my_malloc(k*sizeof(row_t));
	row_t row_pivot;
	row_pivot.bytes = my_malloc((k * sizeof(char)));
	//Check if we have a row or colum with only ones! if so --> error
	for(i = 0 ; i < k; ++i)
	{
		check1 = 0;
		check2 = 0;
		for (j = 0; j < k; ++j)
		{
			check1 = check1 | bytes[j][i];
			check2 = check2 | bytes[i][j];
		}
		if(check1 == 0 || check2 ==0)
		{
			error("calculate_secret_bytes : there was a column or row with all ceros");
			return ERROR;
		}
		rows[i].b = bs[i];
		rows[i].bytes = bytes[i];
		rows[i].index = i;
	}
	////

	//Start gauss
	for(i = 0 ; i < k ; ++i)
	{
		for(j = i ; j < k ; ++j)
		{
			if(rows[i].bytes[j] != 0)
			{
				swap_rows(&rows[i], &rows[j]);
				break;
			}
		}
		error("calculate_secret_bytes : The equations where linear or an error has ocurre!");
		unsigned char x = 0;
		for(j = (i + 1) ; j < k ; ++j)
		{
			if(rows[j].bytes[i] == 0)
				continue;
			memcpy(row_pivot.bytes, rows[i].bytes, k * sizeof(char));
			row_pivot.b = rows[i].b;
			x = divide(rows[j].bytes[i],row_pivot.bytes[i] );
			x_mul_row( x,&row_pivot, k );
			row_sub_row(&rows[j] , &row_pivot, k);
			if(rows[j].bytes[i] != 0 )
			{
				error("calculate_secret_bytes: ERROR!!!");
			}

		}

	}
	//For every row sum all coeff * x_j and get the x_i
	unsigned char suma;
	for(i = (k-1); i >= 0 ; --i)
	{
		suma = 0;
		for(j = i ; j < k ; ++j)
		{
			suma = sum(suma, mul(recover_bytes[j], rows[i].bytes[j]));
		}
		suma = sub(rows[i].b , suma);
		recover_bytes[i] = divide(suma, rows[i].bytes[i]);
	}
	return OK;
}


int
get_secret(int k,simple_8bits_BMP_t ** shadows, simple_8bits_BMP_t * secret )
{
	unsigned char*  bs = my_malloc(k * sizeof(unsigned char));
	int status = OK;
//	unsigned char ** bytes = my_malloc(k  * sizeof(char*));
	unsigned char * recover_bytes = my_malloc(k * sizeof(char));
	if(k < 2 || k > 4 || shadows ==NULL)
	{
		error("get_secret: Error in the paramenters");
		return ERROR;
	}
	int i = 0;
	int j = 0;
	unsigned char ** bytes = my_malloc(k * sizeof(char*));
	img_with_state_t ** shads = my_malloc(sizeof(img_with_state_t*) * k);
	img_with_state_t * sec = new_one_step_in_img(secret, k);
	for(i =0 ; i < k ; ++i)
	{
		shads[i] = new_one_step_in_img(shadows[i], k);
	}
	for(i = 0 ; i < (shads[0]->img->dib_header->height * shads[0]->img->dib_header->width / k) + 1 ; ++i)
	{
		status = one_step_in_img(sec);
		status = one_step_in_imgs(shads, k);
		for (j = 0; j < k; ++j) {
			bs[j] = get_b_from_pixels(k,shads[j]->current_bytes);
			bytes[j] = shads[j]->current_bytes;
			status = get_k_coefficients(bytes[j], k, bytes[j]);
		}
		status = calculate_secret_bytes(bytes, bs, recover_bytes, k );
		for ( j = 0; j < k; ++j)
		{
			sec->current_bytes[j] = recover_bytes[j];
		}
	}

	return OK;
}

int
share_secret(int k, int n, simple_8bits_BMP_t * secret, simple_8bits_BMP_t ** shadows)
{
	int i =0;
	int j = 0;
	int status = 0;
	img_with_state_t *sec;
	unsigned char ** bytes = my_malloc(n * sizeof(char*));
	unsigned char b = 0x00;
	if(k > n)
	{
		return ERROR;
	}
	img_with_state_t ** shads = my_malloc(sizeof(img_with_state_t*) * n);
	sec = new_one_step_in_img(secret, k);
	for(i =0 ; i < n ; ++i)
	{
		shads[i] = new_one_step_in_img(shadows[i], k);
	}
	for(i = 0 ; i < (secret->dib_header->height * secret->dib_header->width / k) + 1 ; ++i)
	{
		status = one_step_in_img(sec);
		status = one_step_in_imgs(shads, n);
		for(j = 0; j < n ; ++j)
		{
			bytes[j] = shads[j]->current_bytes;
			get_k_coefficients_no_cero(bytes[j], k, bytes[j]);
		}
		make_linear_independent(bytes, k, n);
		for(j = 0; j< n ; ++j)
		{
			b = calculate_b(bytes[j], sec->current_bytes, k);
			save_b_to_coefficients(b, k,bytes[j]);
		}
	//	cal
	}
	my_free(bytes);
	return OK;
}


//IMAGE SHOULD HAVE 1 pixel black every 2 pixels!
//int
//main(void)
//{
//	int i = 0;
////	printf("am I working??");
//	simple_8bits_BMP_t * img;
//	img = load_bmp_from_file("./misc/bmps300x450/Albert.bmp");
//	img_with_state_t * img_state;
//	img_state = new_one_step_in_img(img, 2);
//	while(i < 300*450){
//		one_step_in_img(img_state);
//		img_state->current_bytes[1] = 0x00;
//
//		printf("i = %d \n", i++);
//	}
//	save_bmp_to_file(img_state->img, "./misc/out.bmp");
//	printf("img is %p", img_state);
//}




//int
//main(void)
//{
//	int i = 0;
////	printf("am I working??");
//	simple_8bits_BMP_t * img;
//	img = load_bmp_from_file("./misc/bmps300x450/Albert.bmp");
//	img_with_state_t * img_state;
//	img_state = new_one_step_in_img(img, 2);
//	while(i < 300*450){
//		if(one_step_in_img(img_state) == DONE){
////			printf("DONE \n");
////			break;
//		}
//		printf("i = %d \n", i++);
//	}
//	save_bmp_to_file(img_state->img, "./misc/out.bmp");
//	printf("img is %p", img_state);
//}
//
