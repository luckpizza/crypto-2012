/*
 * share_secret_utils.c
 *
 *  Created on: Jun 5, 2012
 *      Author: luckpizza
 */

#include "mod251_operations.h"
#include "debug.h"
#include "status_definitions.h"
/**
 * given a group fo coefficients and secret bytes, it calculates the "b" to
 * be stored as a secret!
 */
unsigned char
calculate_b(unsigned char * coefficients,unsigned char * secret_bytes, int amount)
{
	if(amount < 1){
		error("error calculation b, amount to small \n");
		exit(-1);
	}
	int i = 0;
	unsigned char rta = 0;
	for(i = 0; i < amount; ++i)
	{
		rta = sum(rta,mul( coefficients[i], secret_bytes[i]));
	}
	return rta;
}

int
make_linear_independent(unsigned char ** data, int k , int n)
{

}

/**
 * return 1 if independent, 0 if not
 */
int
are_linear_independent(unsigned char * v1, unsigned char * v2, int amount)
{
	if(amount < 1){
		error("error in are_linear_independent , amount to small \n");
		exit(-1);
	}
	unsigned char tmp = 0;
	int i = 1;
	tmp = divide(v1[0], v2[0]);
	while(i < amount)
	{
		if(divide(v1[i], v2[i]) != tmp)
		{
			return YES;
		}
		++i;
	}
	return NO;
}

//int
//main(void)
//{
//	unsigned char coeff[3] = {7,12,27};
//	unsigned char coeff1[3] = {14,24,54};
//
//	unsigned char sec[3] = {110, 24, 72};
//
//	int rta = calculate_b(coeff, sec, 3);
//	printf("b is %d \n", rta);
//	rta = are_linear_independent(coeff, coeff1, 3);
//	printf("they are NOT lineal_indep!! are they? %d \n", rta);
//	rta = are_linear_independent(coeff, sec, 3);
//	printf("they are lineal_indep!! are they? %d \n", rta);
//	return 1;
//}
