/*
 * bit_wise.c
 *
 *  Created on: Jun 4, 2012
 *      Author: luckpizza
 */

#include "debug.h"
#include "status_definitions.h"
int
get_k_coefficients(const unsigned char *src , int k, unsigned char *dst )
{
	int rta = OK;
	switch (k) {
		case 2:
			dst[0] = src[0] >>4;
			dst[1] = src[1] >>4;
			debug("getting Coefficients for k = 2 d1 = %d", dst[1]);
			break;
		case 3:
			dst[0] = src[0] >>3;
			dst[1] = src[1] >>3;
			dst[2] = src[2] >>2;
			debug("getting Coefficients for k = 3 d1 = %d ,  d2 = %d , d3= %d \n", dst[0], dst[1], dst[2]);

			break;
		case 4:
			dst[0] = src[0] >>2;
			dst[1] = src[1] >>2;
			dst[2] = src[2] >>2;
			dst[3] = src[3] >>2;
			debug("getting Coefficients for k = 4 d1 = %d", dst[1]);

			break;
		default:
			rta = ERROR;
			break;
	}
	return rta;

}

int
save_b_to_coefficients(const unsigned char b , int k, unsigned char *dst )
{
	int rta = OK;
		switch (k) {
			case 2:
				dst[0] = (dst[0] & 0xF0) | (b & 0x0F);
				dst[1] = (dst[1] & 0xF0) |  (b >>4);
				debug("getting Coefficients for k = 2 d1 = %d", dst[1]);
				break;
			case 3:
				dst[0] = (dst[0] & 0xF8) | (b & 0x07);
				dst[1] = (dst[1] & 0xF8) | (b>>3 & 0x07);
				dst[2] = (dst[2] & 0xFC) | (b>>6 );
				debug("dst[2] = %d , (dst[2] & 0xFC) = %d , (b>>6 ) = %d",dst[2],  (dst[2] & 0xFC),(b>>6 ) );
				debug("saving b to Coefficients for k = 3 d1 = %d ,  d2 = %d , d3= %d \n", dst[0], dst[1], dst[2]);

				break;
			case 4:
				dst[0] = (dst[0] & 0xFC) | (b & 0x03);
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

int
main(void)
{
	unsigned char src[3] = {0xFF, 0xFF, 0xFF};
	unsigned char dst[3] = {0x00 , 0x00, 0x00};
//	get_k_coefficients(src, 3, dst);
	unsigned char b = 0xFF;
	save_b_to_coefficients(b, 3, dst);
}

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
