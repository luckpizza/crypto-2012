/*
 * bit_wise.c
 *
 *  Created on: Jun 4, 2012
 *      Author: luckpizza
 */

#include "debug.h"
#include "status_definitions.h"
#include <openssl/md5.h>


/*
 * It already have th parity bit in 0
 */
int
get_k_coefficients(const unsigned char *src , int k, unsigned char *dst )
{
	int rta = OK;
	switch (k) {
		case 2:
			dst[0] = src[0] & 0xE0;
			dst[1] = src[1] & 0xF0;
			debug("getting Coefficients for k = 2 d1 = %d", dst[1]);
			break;
		case 3:
			dst[0] = src[0] & 0xF8;
			dst[1] = src[1] & 0xF8;
			dst[2] = src[2] & 0xF8;
			debug("getting Coefficients for k = 3 d1 = %d ,  d2 = %d , d3= %d \n", dst[0], dst[1], dst[2]);

			break;
		case 4:
			dst[0] = src[0] & 0xF8;
			dst[1] = src[1] & 0xFC;
			dst[2] = src[2] & 0xFC;
			dst[3] = src[3] & 0xFC;
			debug("getting Coefficients for k = 4 d1 = %d", dst[1]);

			break;
		default:
			rta = ERROR;
			break;
	}
	return rta;

}


///* THE GOOD ONEs!
// * It already have th parity bit in 0
// */
//int
//get_k_coefficients(const unsigned char *src , int k, unsigned char *dst )
//{
//	int rta = OK;
//	switch (k) {
//		case 2:
//			dst[0] = src[0] >>5;
//			dst[1] = src[1] >>4;
//			debug("getting Coefficients for k = 2 d1 = %d", dst[1]);
//			break;
//		case 3:
//			dst[0] = src[0] >>3;
//			dst[1] = src[1] >>3;
//			dst[2] = src[2] >>3;
//			debug("getting Coefficients for k = 3 d1 = %d ,  d2 = %d , d3= %d \n", dst[0], dst[1], dst[2]);
//
//			break;
//		case 4:
//			dst[0] = src[0] >>3;
//			dst[1] = src[1] >>2;
//			dst[2] = src[2] >>2;
//			dst[3] = src[3] >>2;
//			debug("getting Coefficients for k = 4 d1 = %d", dst[1]);
//
//			break;
//		default:
//			rta = ERROR;
//			break;
//	}
//	return rta;
//
//}
/**
 * This function is the same as get_k_coefficients but
 * it  don't let all coefficients to be 0!
 *
 */
int
get_k_coefficients_no_cero(const unsigned char *src , int k, unsigned char *dst )
{
	int i = 0;
	int tmp = 0;
	if(get_k_coefficients(src, k, dst) == ERROR)
		return ERROR;
	for (i = 0; i < k; ++i)
	{
		if( dst[i] != 0 )
			return OK;
	}
	i = (((double)rand()) /RAND_MAX) * (k-1);
	dst[i] = 0x01;
	return OK;
}

/*
 * it already have the parity bit in 0
 */
int
save_b_to_coefficients(const unsigned char b , int k, unsigned char *dst )
{// unsigned char b = 0xFF;
	int rta = OK;
		switch (k) {
			case 2:
				dst[0] = (dst[0]<<5 & 0xE0) | (b & 0x0F);
				dst[1] = (dst[1]<<4 & 0xF0) |  (b >>4);
				debug("getting Coefficients for k = 2 d1 = %d", dst[1]);
				break;
			case 3:
				dst[0] = (dst[0]<<3 & 0xF8) | (b & 0x03);
				dst[1] = (dst[1]<<3 & 0xF8) | (b>>2 & 0x07);
				dst[2] = (dst[2]<<3 & 0xF8) | (b>>5 );
				debug("dst[2] = %d , (dst[2] & 0xFC) = %d , (b>>6 ) = %d",dst[2],  (dst[2] & 0xFC),(b>>6 ) );
				debug("saving b to Coefficients for k = 3 d1 = %d ,  d2 = %d , d3= %d \n", dst[0], dst[1], dst[2]);

				break;
			case 4:
				dst[0] = (dst[0]<<3 & 0xF8) | (b & 0x03);
				dst[1] = (dst[1]<<2 & 0xFC) | (b>>2 & 0x03);
				dst[2] = (dst[2]<<2 & 0xFC) | (b>>4 & 0x03);
				dst[3] = (dst[3]<<2 & 0xFC) | (b>>6 & 0x03);
				debug("getting Coefficients for k = 4 d1 = %d", dst[1]);

				break;
			default:
				rta = ERROR;
				break;
		}
		return rta;
}

/*
 * it already have the parity bit in 0
 */
unsigned char
get_b_from_pixels( int k, unsigned char *dst )
{// unsigned char b = 0xFF;
	unsigned char b = 0;
 		switch (k) {
			case 2:
				b = (dst[1] & 0x0F)<<4;
				b = b | (dst[0] & 0x0F);
				debug("getting b for k = 2 b = %d \n", b);
				break;
			case 3:
				b = (dst[2] & 0x07);
				b = (b<<3) | (dst[1] & 0x07);
				b = (b<<2) | (dst[0] & 0x03);
				debug("getting b for k = 3 b = %d \n", b);
				break;
			case 4:
				b = (dst[3] & 0x03);
				b = (b<<2) | (dst[2] & 0x03);
				b = (b<<2) | (dst[1] & 0x03);
				b = (b<<2) | (dst[0] & 0x03);
				debug("getting b for k = 4 b = %d \n", b);
				break;
			default:
				error("get_b_from_pixels error");
				b = 255;
				break;
		}
		return b;
}

///*
// * it already have the parity bit in 0
// */
//unsigned char
//get_b_from_pixels( int k, unsigned char *dst )
//{// unsigned char b = 0xFF;
//	unsigned char b = 0;
// 		switch (k) {
//			case 2:
//				b = (dst[0] & 0x0F);
//				b = (b<<4) | (dst[1] & 0x0F);
//				debug("getting b for k = 2 b = %d \n", b);
//				break;
//			case 3:
//				b = (dst[0] & 0x03);
//				b = (b<<3) | (dst[1] & 0x07);
//				b = (b<<3) | (dst[2] & 0x07);
//				debug("getting b for k = 3 b = %d \n", b);
//				break;
//			case 4:
//				b = (dst[0] & 0x03);
//				b = (b<<2) | (dst[1] & 0x03);
//				b = (b<<2) | (dst[2] & 0x03);
//				b = (b<<2) | (dst[3] & 0x03);
//				debug("getting b for k = 4 b = %d \n", b);
//				break;
//			default:
//				error("get_b_from_pixels error");
//				b = 255;
//				break;
//		}
//		return b;
//}



int
save_b_to_original_pixel(const unsigned char b , int k, unsigned char *dst )
{
	int rta = OK;
		switch (k) {
			case 2:
				dst[0] = (dst[0] & 0xE0) | (b & 0x0F);
				dst[1] = (dst[1] & 0xF0) |  (b >>4);
				debug("getting Coefficients for k = 2 d1 = %d", dst[1]);
				break;
			case 3:
				dst[0] = (dst[0] & 0xF8) | (b & 0x03);
				dst[1] = (dst[1] & 0xF8) | (b>>2 & 0x07);
				dst[2] = (dst[2] & 0xF8) | (b>>5 );
				debug("dst[2] = %d , (dst[2] & 0xFC) = %d , (b>>6 ) = %d",dst[2],  (dst[2] & 0xFC),(b>>6 ) );
				debug("saving b to Coefficients for k = 3 d1 = %d ,  d2 = %d , d3= %d \n", dst[0], dst[1], dst[2]);

				break;
			case 4:
				dst[0] = (dst[0] & 0xF8) | (b & 0x03);
				dst[1] = (dst[1] & 0xFC) | (b>>2 & 0x03);
				dst[2] = (dst[2] & 0xFC) | (b>>4 & 0x03);
				dst[3] = (dst[3] & 0xFC) | (b>>6 & 0x03);
				debug("getting Coefficients for k = 4 d1 = %d", dst[1]);

				break;
			default:
				rta = ERROR;
				break;
		}
		return rta;
}
unsigned char
xor_between_bits(const unsigned char * bits, int amount_of_bytes)
{
	int i = 0;
	int j = 0;
	unsigned char rta = 0x00;
	while( i < amount_of_bytes)
	{
		for( j = 0 ; j < 8; ++j){
			rta = (bits[i]>>j & 0x01)^rta;

		}
		++i;
	}
	debug("final answer of xor_bits is %d", rta);
	return rta;

}

unsigned char
get_md5_parity_bit(const unsigned char * src, int lenght)
{
	unsigned char md5_digest[MD5_DIGEST_LENGTH];
	MD5(src, lenght, md5_digest);
	return xor_between_bits(md5_digest, MD5_DIGEST_LENGTH);
  //  SHA256((unsigned char*) passwordAndSalt, strlen(passwordAndSalt), SHA256Password);

}



//int
//main(void)
//{
////	unsigned char src[3] = {0xFF, 0xFF, 0xFF};
////	unsigned char dst[3] = {0x00 , 0x00, 0x00};
//////	get_k_coefficients(src, 3, dst);
////	unsigned char b = 0xFF;
////	save_b_to_coefficients(b, 3, dst);
//////	unsigned char b_bits = xor_between_bits(src, 3);
////	unsigned char b_bits = get_md5_parity_bit(src, 3);
////	debug("FF div FF = %d \n", divide(0xFF, 0xFF));
////	debug("CF div CF = %d \n", divide(0xCF, 0xCF));
////	debug("FF div 11 = %d \n", divide(0xFF, 0x11));
//	unsigned char src[3]  = {0x03, 0x07, 0x00};
//	int b = get_b_from_pixels( 3, src);
//	printf("b = %d", b);
//
//}
//




//int
//save_k_coefficients(const unsigned int *src , int k, unsigned char *dst )
//{
//	int rta = OK;
//		switch (k) {
//			case 2:
//				dst[1] = (dst[1] & 0xF0) | (src[1] & 0x0F);
//				dst[2] = (dst[2] & 0xF0) | (src[2] & 0x0F);
//				debug("getting Coefficients for k = 2 d1 = %d", dst[1]);
//				break;
//			case 3:
//				dst[1] = (dst[1] & 0xF8) | (src[1] & 0x07);
//				dst[2] = (dst[2] & 0xF8) | (src[2] & 0x07);
//				dst[3] = (dst[3] & 0xFC) | (src[3] & 0x03);
//				debug("getting Coefficients for k = 3 d1 = %d", dst[1]);
//
//				break;
//			case 4:
//				dst[1] = (dst[1] & 0xFC) | (src[1] & 0x03);
//				dst[1] = (dst[1] & 0xFC) | (src[1] & 0x03);
//				dst[3] = (dst[3] & 0xFC) | (src[3] & 0x03);
//				dst[4] = (dst[4] & 0xFC) | (src[4] & 0x03);
//				debug("getting Coefficients for k = 4 d1 = %d", dst[1]);
//
//				break;
//			default:
//				rta = ERROR;
//				break;
//		}
//		return rta;
//}
