/*
 * share_secret_utils.c
 *
 *  Created on: Jun 5, 2012
 *      Author: luckpizza
 */

#include "mod251_operations.h"
#include "debug.h"
#include "status_definitions.h"
#include "share_secret_utils.h"
#include "memory_utils.h"
#include "string.h"
/**
 * given a group fo coefficients and secret bytes, it calculates the "b" to
 * be stored as a secret!
 */
unsigned char
calculate_b(unsigned char * coefficients,unsigned char * secret_bytes, int k)
{
	if(k < 1){
		error("error calculation b, amount to small \n");
		exit(-1);
	}
	int i = 0;
	unsigned char rta = 0;
	for(i = 0; i < k; ++i)
	{
		rta = sum(rta,mul( coefficients[i], secret_bytes[i]));
	}
	return rta;
}

//TODO: perfectionate this function in order to prevent looping over 251
void modify_one_byte(unsigned char *data, int k)
{
	int i = (((double)rand()) /RAND_MAX) * (k-1);
	int to_move = 0;
	i = rand() % k;
	data[i] = (data[i]+1) %251;
	if(data[i] == 0)
		data[i] = 0x01;
	if(k == 2){
		to_move = 4;
		if(i == 0){
			to_move = 5;
		}
		if((data[i]<<to_move & 0xF0) == 0)
		{
			data[i] = 0x01;
		}
	}

	if(k == 3){
			to_move = 3;
			if((data[i]<<to_move & 0xF8 ) == 0)
			{
				data[i] = 0x01;
			}
		}
	if(k == 4){
			to_move = 2;
			if(i == 0){
				to_move = 3;
			}
			if((data[i]<<to_move & 0xFC ) == 0)
			{
				data[i] = 0x01;
			}
		}
//	}
}
/*
 * Triangulates the matrix and returs if it is not scd
 * return: -1 if everything is ok or the row with a problem
 *
 */

int
triangulate_matrix(row_t * rows, int k){
	int rta = -1;
	int tmp = 0;
	int i,j,l;
	int check1, check2;
	int p,q;
	char * recover_bytes = my_malloc(k*sizeof(char));
	row_t row_pivot;
	row_pivot.bytes = my_malloc((k * sizeof(char)));
	memset(recover_bytes, 0, k * sizeof(unsigned char));
	//Check if we have a row or colum with only ones! if so --> error

	for(i = 0 ; i < k- 1 ; ++i)
	{
		for(j = i ; j < k ; ++j)
		{
			if(rows[j].bytes[i] != 0)
			{
				swap_rows(&rows[i], &rows[j]);
				break;
			}
		}
		if(rows[i].bytes[i] == 0)
		{
			rta = rows[i].index;
			my_free(row_pivot.bytes);
			my_free(recover_bytes);
			return rta;
		}
		unsigned char x = 0;
		for(j = (i + 1) ; j < k ; ++j)
		{
			memcpy(row_pivot.bytes, rows[i].bytes, k * sizeof(char));
			row_pivot.b = rows[i].b;
			x = divide(rows[j].bytes[i],row_pivot.bytes[i] );
			x_mul_row( x,&row_pivot, k );
			row_sub_row(&rows[j] , &row_pivot, k);
			//TODO: Test if a row is all ceros and quit!!
			if(rows[j].bytes[i] != 0 )
			{
				fprintf(stderr, "calculate_secret_bytes: ERROR!!! \n");
			}
			tmp = 0;
			for(l = 0; l< k;++l )
			{
				tmp = rows[j].bytes[l] | tmp;
			}
			if(tmp == 0)
			{
				rta = rows[j].index;
				my_free(row_pivot.bytes);
				my_free(recover_bytes);
				return rta;
			}
			if(rta == -1){
				for(p = 0 ; p < k; ++p)
				{
					check1 = 0;
					check2 = 0;
					for (q = 0; q < k; ++q)
					{
						check1 = check1 | rows[q].bytes[p];
						check2 = check2 | rows[p].bytes[q];
					}
					if(check1 == 0 || check2 ==0)
					{
						error("calculate_secret_bytes : there was a column or row with all ceros");
						return ERROR;
					}

				}
			}
		}

	}
	my_free(row_pivot.bytes);
	my_free(recover_bytes);
	return rta;
}
/**
 *
 * Makes the matrix linear_independent
 */


int
make_linear_independent(unsigned char ** data, int k , int n)
{
	int i = 0;
	int j = 0;
	int l = 0;
	int m = 0;
	int idx_modified;
	int status = MODIFIED;
	int idx_row;
	row_t * rows;
	rows= my_malloc(k * sizeof(row_t));
	for(i = 0 ; i < k ; ++i)
	{
		rows[i].bytes = my_malloc(k * sizeof(unsigned char));
	}
	while(status != OK)
	{
		status = OK;
		i = 0;
		if(k == 2)
		{
			while(status == OK && i < n)
			{
				j = 0;
				while(status == OK && j < n)
				{
					if(j == i)
					{
						++j;
						continue;
					}
					memcpy(rows[0].bytes, data[i], k);
					rows[0].b = 0;
					rows[0].index = i;
					memcpy(rows[1].bytes, data[j], k);
					rows[1].b = 0;
					rows[1].index = j;

					if((idx_modified = triangulate_matrix(rows, k)) != -1)
					{
						modify_one_byte(data[idx_modified], k);
						status = MODIFIED;
					}

					++j;
				}
				++i;
			}
		}
		if(k == 3)
		{
			while(status == OK && i < n)
			{
				j = 0;
				while(status == OK && j < n)
				{
					l =0;
					if(j == i)
					{
						++j;
						continue;
					}
					while(status == OK && l < n)
					{
						if(l == i || l == j)
						{
							++l;
							continue;
						}
						memcpy(rows[0].bytes, data[i], k);
						rows[0].b = 0;
						rows[0].index = i;
						memcpy(rows[1].bytes, data[j], k);
						rows[1].b = 0;
						rows[1].index = j;
						memcpy(rows[2].bytes, data[l], k);
						rows[2].b = 0;
						rows[2].index = l;

						if((idx_modified = triangulate_matrix(rows, k)) != -1)
						{
							modify_one_byte(data[idx_modified], k);
							status = MODIFIED;
						}

						++l;
					}
					++j;
				}
				++i;
			}
		}
		if(k == 4)
		{
			while(status == OK && i < n)
			{
				j = 0;
				while(status == OK && j < n)
				{
					l =0;
					if(j == i)
					{
						++j;
						continue;
					}
					while(status == OK && l < n)
					{
						m = 0;

						if(l == i || l == j)
						{
							++l;
							continue;
						}
						while(status == OK && m < n)
						{
							if(m == i || m == j || m == l)
							{
								++m;
								continue;
							}

							memcpy(rows[0].bytes, data[i], k);
							rows[0].b = 0;
							rows[0].index = i;
							memcpy(rows[1].bytes, data[j], k);
							rows[1].b = 0;
							rows[1].index = j;
							memcpy(rows[2].bytes, data[l], k);
							rows[2].b = 0;
							rows[2].index = l;
							memcpy(rows[3].bytes, data[m], k);
							rows[3].b = 0;
							rows[3].index = m;
							if((idx_modified = triangulate_matrix(rows, k)) != -1)
							{
								modify_one_byte(data[idx_modified], k);
								status = MODIFIED;
							}
							++m;
						}

						++l;
					}
					++j;
				}
				++i;
			}
		}

	}

	for(i = 0 ; i < k ; ++i)
	{
		my_free(rows[i].bytes);
	}
	my_free(rows);
	return OK;
}




int
check_coefficients(unsigned char ** data, int k , int n)
{
	int i = 0;
	int j = 0;
	unsigned char tmp = 0;
	int idx = 0;
	for(i = 0; i < k; ++i)
	{
		for(j = 0; j < k; ++j)
		{
			tmp = data[j][i] | tmp;
//			if(tmp > 0)
//				continue;
		}
		if(tmp == 0)
		{
			idx = rand() % k;
			data[idx][i] = 0x01;
		}
	}
	return 1;
}

/**
 * return 1 if independent, 0 if not
 */
int
are_linear_independent(unsigned char * v1, unsigned char * v2, int amount)
{
	if(amount < 1){
		error("error in are_linear_independent , amount to small \n");
		exit(-1);
	}
	unsigned char tmp = 0;
	int i = 0;
	tmp = divide(v1[0], v2[0]);
	while(i < amount)
	{
		if((v1[i] | v2[i]) != 0 &&( v1[i] == 0 || v2[i] == 0))
			return YES;
		if(divide(v1[i], v2[i]) != tmp)
		{
			return YES;
		}
		++i;
	}
	return NO;
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
}

void
swap_char( unsigned char *a, unsigned char *b)
{
	unsigned char  tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
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

//int
//main(void)
//{
//	unsigned char coeff[3] = {7,12,27};
//	unsigned char coeff1[3] = {14,24,54};
//	unsigned char *cof[2];
//	unsigned char sec[3] = {110, 24, 72};
//	cof[0] = coeff;
//	cof[1] = coeff1;
//	int rta = calculate_b(coeff, sec, 3);
//	printf("b is %d \n", rta);
//	rta = make_linear_independent(cof, 3, 2);
//	printf("they where NOT lineal_indep!! but now are they? %d \n c11 = %d, c12 %d, c13 = %d, c21 =%d, c22 = %d, c23 %d", rta, coeff[0], coeff[1], coeff[2], coeff1[0], coeff1[1], coeff1[2]);
//	rta = are_linear_independent(coeff, sec, 3);
//	printf("they are lineal_indep!! are they? %d \n", rta);
//	return 1;
//}



//int
//main(void)
//{
//	unsigned char coeff[3] = {7,12,27};
//	unsigned char coeff1[3] = {14,24,54};
//
//	unsigned char sec[3] = {110, 24, 72};
//
//	int rta = calculate_b(coeff, sec, 3);
//	printf("b is %d \n", rta);
//	rta = are_linear_independent(coeff, coeff1, 3);
//	printf("they are NOT lineal_indep!! are they? %d \n", rta);
//	rta = are_linear_independent(coeff, sec, 3);
//	printf("they are lineal_indep!! are they? %d \n", rta);
//	return 1;
//}
