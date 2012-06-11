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
//	simple_8bits_BMP_t * img1;
//	simple_8bits_BMP_t * img2;
//	simple_8bits_BMP_t * img3;
//	simple_8bits_BMP_t * img4;
//
//	simple_8bits_BMP_t * sec;
//
//	img1 = load_bmp_from_file("./misc/catedra/v2/4sombras/Angelina4.bmp");
//	img2 = load_bmp_from_file("./misc/catedra/v2/4sombras/Jim4.bmp");
//	img3 = load_bmp_from_file("./misc/catedra/v2/4sombras/Roberto4.bmp");
//	img4 = load_bmp_from_file("./misc/catedra/v2/4sombras/Whitney4.bmp");
//
//	sec = load_bmp_from_file("./misc/catedra/v2/4sombras/Susan4.bmp");
//
////	img1 = load_bmp_from_file("./misc/catedra/v2/3sombras/Albert3.bmp");
////	img2 = load_bmp_from_file("./misc/catedra/v2/3sombras/Alfred3.bmp");
////	img3 = load_bmp_from_file("./misc/catedra/v2/3sombras/Eva3.bmp");
////	sec = load_bmp_from_file("./misc/catedra/v2/3sombras/Gustavo3.bmp");
//
//
//	simple_8bits_BMP_t * shadows[4];
//	shadows[0] = img1;
//	shadows[1] = img2;
//	shadows[2] = img3;
//	shadows[3] = img4;
//
//	share_secret(2, 4, sec, shadows);
//	save_bmp_to_file(img1, "./misc/out1.bmp");
//	save_bmp_to_file(img2, "./misc/out2.bmp");
////	save_bmp_to_file(img3, "./misc/out3.bmp");
////	save_bmp_to_file(img4, "./misc/out4.bmp");
//	get_secret(2, shadows, sec);
////	img_with_state_t * img1_state;
////	img_with_state_t * img2_state;
////	img_with_state_t * img3_state;
////	img_with_state_t * sec_state;
////
////	img1_state = new_one_step_in_img(img1, 2);
////
////	while(i < 300*450){
////		one_step_in_img(img_state);
////		img_state->current_bytes[1] = 0x00;
////
////		printf("i = %d \n", i++);
////	}
//
////	save_bmp_to_file(img_state->img, "./misc/out.bmp");
//	save_bmp_to_file(sec, "./misc/sec.bmp");
//	printf("\n img is %p \n", img1);
//}


int
main(void)
{
	srand(time(NULL));
	int i = 0;
//	printf("am I working??");
	simple_8bits_BMP_t * img1;
	simple_8bits_BMP_t * img2;
	simple_8bits_BMP_t * img3;
	simple_8bits_BMP_t * img4;

	simple_8bits_BMP_t * sec;
	simple_8bits_BMP_t * img_to_sec;
	img1 = load_bmp_from_file("./misc/bmps300x450/Albert.bmp");
	img2 = load_bmp_from_file("./misc/bmps300x450/Alfred.bmp");
	img3 = load_bmp_from_file("./misc/bmps300x450/Carlitos.bmp");
	img4 = load_bmp_from_file("./misc/bmps300x450/Grace.bmp");
	img_to_sec = load_bmp_from_file("./misc/bmps300x450/John.bmp");

	sec = load_bmp_from_file("./misc/bmps300x450/John.bmp");

	simple_8bits_BMP_t * shadows[4];
	shadows[0] = img1;
	shadows[1] = img2;
	shadows[2] = img3;
	shadows[3] = img4;
	share_secret(2, 2, sec, shadows);
	save_bmp_to_file(img1, "./misc/out1.bmp");
	save_bmp_to_file(img2, "./misc/out2.bmp");
	//save_bmp_to_file(img3, "./misc/out3.bmp");
//	save_bmp_to_file(img4, "./misc/out4.bmp");
	get_secret(2, shadows, sec);

	save_bmp_to_file(sec, "./misc/sec.bmp");
	printf("\n img is %p \n", img1);
}




//int
//main(void)
//{
//	int i = 0;
////	printf("am I working??");
//	simple_8bits_BMP_t * img1;
//	simple_8bits_BMP_t * img2;
//	simple_8bits_BMP_t * img3;
//	simple_8bits_BMP_t * img4;
//
//	simple_8bits_BMP_t * sec;
//
//	img1 = load_bmp_from_file("./misc/catedra/v2/2sombras/Gandhi2.bmp");
//	img2 = load_bmp_from_file("./misc/catedra/v2/2sombras/Grace2.bmp");
//	img3 = load_bmp_from_file("./misc/catedra/v2/4sombras/Roberto4.bmp");
//	img4 = load_bmp_from_file("./misc/catedra/v2/4sombras/Whitney4.bmp");
//
//	sec = load_bmp_from_file("./misc/catedra/v2/2sombras/Grace2.bmp");
//
////	img1 = load_bmp_from_file("./misc/catedra/v2/3sombras/Albert3.bmp");
////	img2 = load_bmp_from_file("./misc/catedra/v2/3sombras/Alfred3.bmp");
////	img3 = load_bmp_from_file("./misc/catedra/v2/3sombras/Eva3.bmp");
////	sec = load_bmp_from_file("./misc/catedra/v2/3sombras/Gustavo3.bmp");
//
//
//	simple_8bits_BMP_t * shadows[4];
//	shadows[0] = img1;
//	shadows[1] = img2;
//	shadows[2] = img3;
//	shadows[3] = img4;
//
//	//	share_secret(3, 4, sec, shadows);
////	save_bmp_to_file(img1, "./misc/out1.bmp");
////	save_bmp_to_file(img2, "./misc/out2.bmp");
////	save_bmp_to_file(img3, "./misc/out3.bmp");
////	save_bmp_to_file(img4, "./misc/out4.bmp");
//	get_secret(2, shadows, sec);
////	img_with_state_t * img1_state;
////	img_with_state_t * img2_state;
////	img_with_state_t * img3_state;
////	img_with_state_t * sec_state;
////
////	img1_state = new_one_step_in_img(img1, 2);
////
////	while(i < 300*450){
////		one_step_in_img(img_state);
////		img_state->current_bytes[1] = 0x00;
////
////		printf("i = %d \n", i++);
////	}
//
////	save_bmp_to_file(img_state->img, "./misc/out.bmp");
//	save_bmp_to_file(sec, "./misc/sec.bmp");
//	printf("img is %p", img1);
//}
//


//int
//main(void)
//{
//	int i = 0;
////	printf("am I working??");
//	simple_8bits_BMP_t * img1;
//	simple_8bits_BMP_t * img2;
//	simple_8bits_BMP_t * img3;
//	simple_8bits_BMP_t * img4;
//
//	simple_8bits_BMP_t * sec;
//
////	img1 = load_bmp_from_file("./misc/catedra/v2/sombras/Gandhi2.bmp");
////	img2 = load_bmp_from_file("./misc/catedra/v2/2sombras/Grace2.bmp");
////	img3 = load_bmp_from_file("./misc/catedra/v2/4sombras/Roberto4.bmp");
////	img4 = load_bmp_from_file("./misc/catedra/v2/4sombras/Whitney4.bmp");
//
////	sec = load_bmp_from_file("./misc/catedra/v2/2sombras/Grace2.bmp");
//
//	img1 = load_bmp_from_file("./misc/catedra/v2/3sombras/Albert3.bmp");
//	img2 = load_bmp_from_file("./misc/catedra/v2/3sombras/Alfred3.bmp");
//	img3 = load_bmp_from_file("./misc/catedra/v2/3sombras/Eva3.bmp");
//	sec = load_bmp_from_file("./misc/catedra/v2/3sombras/Gustavo3.bmp");
//
//
//	simple_8bits_BMP_t * shadows[4];
//	shadows[0] = img1;
//	shadows[1] = img2;
//	shadows[2] = img3;
//	shadows[3] = img4;
//
//	//	share_secret(3, 4, sec, shadows);
////	save_bmp_to_file(img1, "./misc/out1.bmp");
////	save_bmp_to_file(img2, "./misc/out2.bmp");
////	save_bmp_to_file(img3, "./misc/out3.bmp");
////	save_bmp_to_file(img4, "./misc/out4.bmp");
//	get_secret(3, shadows, sec);
////	img_with_state_t * img1_state;
////	img_with_state_t * img2_state;
////	img_with_state_t * img3_state;
////	img_with_state_t * sec_state;
////
////	img1_state = new_one_step_in_img(img1, 2);
////
////	while(i < 300*450){
////		one_step_in_img(img_state);
////		img_state->current_bytes[1] = 0x00;
////
////		printf("i = %d \n", i++);
////	}
//
////	save_bmp_to_file(img_state->img, "./misc/out.bmp");
//	save_bmp_to_file(sec, "./misc/sec.bmp");
//	printf("img is %p", img1);
//}



//int
//main(void)
//{
//	int i = 0;
////	printf("am I working??");
//	simple_8bits_BMP_t * img1;
//	simple_8bits_BMP_t * img2;
//	simple_8bits_BMP_t * img3;
//	simple_8bits_BMP_t * img4;
//
//	simple_8bits_BMP_t * sec;
//
////	img1 = load_bmp_from_file("./misc/catedra/v2/sombras/Gandhi2.bmp");
////	img2 = load_bmp_from_file("./misc/catedra/v2/2sombras/Grace2.bmp");
////	img3 = load_bmp_from_file("./misc/catedra/v2/4sombras/Roberto4.bmp");
////	img4 = load_bmp_from_file("./misc/catedra/v2/4sombras/Whitney4.bmp");
//
////	sec = load_bmp_from_file("./misc/catedra/v2/2sombras/Grace2.bmp");
//
//	img1 = load_bmp_from_file("./misc/catedra/v2/3sombras/Albert3.bmp");
//	img2 = load_bmp_from_file("./misc/catedra/v2/3sombras/Alfred3.bmp");
//	img3 = load_bmp_from_file("./misc/catedra/v2/3sombras/Eva3.bmp");
//	sec = load_bmp_from_file("./misc/catedra/v2/3sombras/Gustavo3.bmp");
//
//
//	simple_8bits_BMP_t * shadows[4];
//	shadows[0] = img1;
//	shadows[1] = img2;
//	shadows[2] = img3;
//	shadows[3] = img4;
//
//	//	share_secret(3, 4, sec, shadows);
////	save_bmp_to_file(img1, "./misc/out1.bmp");
////	save_bmp_to_file(img2, "./misc/out2.bmp");
////	save_bmp_to_file(img3, "./misc/out3.bmp");
////	save_bmp_to_file(img4, "./misc/out4.bmp");
////	get_secret(3, shadows, sec);
//	img_with_state_t * img_state = new_one_step_in_img(img1, 3);
//	i = 0;
//	while(one_step_in_img(img_state) != DONE)
//	{
//		++i;
//	}
//	printf("i is =%d \n",  i);
//	save_bmp_to_file(img1, "./misc/step.bmp");
//
////	img_with_state_t * img1_state;
////	img_with_state_t * img2_state;
////	img_with_state_t * img3_state;
////	img_with_state_t * sec_state;
////
////	img1_state = new_one_step_in_img(img1, 2);
////
////	while(i < 300*450){
////		one_step_in_img(img_state);
////		img_state->current_bytes[1] = 0x00;
////
////		printf("i = %d \n", i++);
////	}
//
////	save_bmp_to_file(img_state->img, "./misc/out.bmp");
//	save_bmp_to_file(sec, "./misc/sec.bmp");
//	printf("img is %p", img1);
//}
//
//
//

