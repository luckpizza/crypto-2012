/*
 * share_secret.h
 *
 *  Created on: Jun 5, 2012
 *      Author: luckpizza
 */

#ifndef SHARE_SECRET_H_
#define SHARE_SECRET_H_

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
new_one_step_in_img(simple_8bits_BMP_t * img,int k);

/**
 * makes imgs created by @see new_one_step_in_img go one iteration fordware
 * saving the modifications to the image.
 */
int
one_step_in_img(img_with_state_t * img);


int
share_secret(int k, int n, simple_8bits_BMP_t * secret, simple_8bits_BMP_t ** shadows);
#endif /* SHARE_SECRET_H_ */
