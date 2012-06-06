/*
 * main.c
 *
 *  Created on: May 31, 2012
 *      Author: luckpizza
 */

#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "share_secret.h"
#include "status_definitions.h"

int
main(void)
{
	int i = 0;
//	printf("am I working??");
	simple_8bits_BMP_t * img1;
	simple_8bits_BMP_t * img2;
	simple_8bits_BMP_t * img3;
	simple_8bits_BMP_t * sec;

	img1 = load_bmp_from_file("./misc/bmps300x450/Albert.bmp");
	img2 = load_bmp_from_file("./misc/bmps300x450/Alfred.bmp");
	img3 = load_bmp_from_file("./misc/bmps300x450/John.bmp");
	sec = load_bmp_from_file("./misc/bmps300x450/James.bmp");

	simple_8bits_BMP_t * shadows[3];
	shadows[0] = img1;
	shadows[1] = img2;
	shadows[2] = img3;
	share_secret(3, 3, sec, shadows);
//	img_with_state_t * img1_state;
//	img_with_state_t * img2_state;
//	img_with_state_t * img3_state;
//	img_with_state_t * sec_state;
//
//	img1_state = new_one_step_in_img(img1, 2);
//
//	while(i < 300*450){
//		one_step_in_img(img_state);
//		img_state->current_bytes[1] = 0x00;
//
//		printf("i = %d \n", i++);
//	}

//	save_bmp_to_file(img_state->img, "./misc/out.bmp");
	save_bmp_to_file(img1, "./misc/out1.bmp");
	save_bmp_to_file(img2, "./misc/out2.bmp");
	save_bmp_to_file(img3, "./misc/out3.bmp");

	printf("img is %p", img1);
}
