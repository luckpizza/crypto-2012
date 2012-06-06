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
