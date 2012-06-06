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


typedef struct img_with_state{
	simple_8bits_BMP_t * img;
	unsigned char * current_bytes;
	int i;
	int j;
	int k;
}img_with_state_t;
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
	}
	return OK;
}

int
share_secret(int k, int n, simple_8bits_BMP_t * secret, simple_8bits_BMP_t ** shadows)
{
	if(k > n)
	{
		return ERROR;
	}


	return OK;
}


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
