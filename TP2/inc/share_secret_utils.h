/*
 * share_secret_utils.h
 *
 *  Created on: Jun 5, 2012
 *      Author: luckpizza
 */

#ifndef SHARE_SECRET_UTILS_H_
#define SHARE_SECRET_UTILS_H_


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
