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

typedef struct img_with_state{
	simple_8bits_BMP_t * img;
	unsigned char * current_bytes;
	int i;
	int j;
	int k;
}img_with_state_t;

img_with_state_t *
new_one_step_in_img(simple_8bits_BMP_t * img,int k)
{
	img_with_state_t * rta = my_malloc(sizeof(img_with_state_t));
	if(img == NULL)
	{
		error("Trying to initializate state of a NULL img");
		return NULL;
	}

	rta->current_bytes = my_malloc(k * sizeof(unsigned char));
	rta->i = 0;
	rta->j = 0;
	rta->k = k;
	rta->img = img;

	return rta;
}

int
one_step_in_img(img_with_state_t * img)
{
	int idx = 0;
	int i =0, j = 0 ;
	if(img == NULL || img->img ==NULL || img->k ==0 || img->current_bytes == NULL){
		error("trying to make one step to a wrong file!");
	}
	if(img->i != 0 && img->j != 0)
	{
		while(idx < img->k)
		{
			if(img->j < img->img->dib_header->width)
			{
				img->img->img[img->i][img->j] = img->current_bytes[idx];
				++img->j;
			}else if(img->i < img->img->dib_header->height)
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
	idx = 0;
	j = img->j ;
	i = img->i;
	while(idx < img->k)
	{
		if(j < img->img->dib_header->width)
		{
			 img->current_bytes[idx] = img->img->img[i][j];
			++j;
		}else if(i < img->img->dib_header->height)
		{
			++i;
			j = 0;
			 img->current_bytes[idx] = img->img->img[i][j];
		}else
		{
			debug(" one_step_in_img : We reach the end of the image");
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
