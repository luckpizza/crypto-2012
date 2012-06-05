/*
 * mod251_operations.h
 *
 *  Created on: Jun 5, 2012
 *      Author: luckpizza
 */

#ifndef MOD251_OPERATIONS_H_
#define MOD251_OPERATIONS_H_

unsigned char
sum(unsigned char a, unsigned char b);

unsigned char
sub(unsigned char a, unsigned char b);

unsigned char
mul(unsigned char a, unsigned char b);

unsigned char
calculate_inverse(unsigned char b);

unsigned char
divide(unsigned char a, unsigned char b);

#endif /* MOD251_OPERATIONS_H_ */
