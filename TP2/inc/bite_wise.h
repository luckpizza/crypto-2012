/*
 * bite_wise.h
 *
 *  Created on: Jun 4, 2012
 *      Author: luckpizza
 */

#ifndef BITE_WISE_H_
#define BITE_WISE_H_

/*
 * it already have the parity bit
 */
int
save_b_to_coefficients(const unsigned char b , int k, unsigned char *dst );
/*
 * It already have th parity bit
 */

int
save_b_to_original_pixel(const unsigned char *src , int k, unsigned char *dst );

//unsigned char
//xor_between_bits(const unsigned char * bits, int amount_of_bytes);

unsigned char
get_md5_parity_bit(const unsigned char * src, int lenght);


/**
 * This function is the same as get_k_coefficients but
 * it  don't let all coefficients to be 0!
 *
 */
int
get_k_coefficients_no_cero(const unsigned char *src , int k, unsigned char *dst );


int
get_k_coefficients(const unsigned char *src , int k, unsigned char *dst );

/*
 * it already have the parity bit in 0
 */
unsigned char
get_b_from_pixels( int k, unsigned char *dst );
#endif /* BITE_WISE_H_ */
