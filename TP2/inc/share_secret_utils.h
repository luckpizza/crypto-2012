/*
 * share_secret_utils.h
 *
 *  Created on: Jun 5, 2012
 *      Author: luckpizza
 */

#ifndef SHARE_SECRET_UTILS_H_
#define SHARE_SECRET_UTILS_H_

typedef struct row{
	unsigned char * bytes;
	unsigned char b;
	int index;
}row_t;

/**
 * given a group fo coefficients and secret bytes, it calculates the "b" to
 * be stored as a secret!
 */
unsigned char
calculate_b(unsigned char * coefficients,unsigned char * secret_bytes, int amount);
/**
 * return 1 if independent, 0 if not
 */
int
are_linear_independent(unsigned char * v1, unsigned char * v2, int amount);
#endif /* SHARE_SECRET_UTILS_H_ */

int
make_linear_independent(unsigned char ** data, int k , int n);
void
swap_rows( row_t * a, row_t * b);
void
swap_char( unsigned char *a, unsigned char *b);

void
x_mul_bytes(unsigned char x, unsigned char * bytes, int k);

void
x_mul_row(unsigned char x, row_t * row, int k);

void
row_sub_row(row_t * a, row_t * b, int k);
