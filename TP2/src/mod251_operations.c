/*
 * mod251_operations.c
 *
 *  Created on: Jun 5, 2012
 *      Author: luckpizza
 */
unsigned char inverse[251];


unsigned char
sum(unsigned char a, unsigned char b)
{
	return (a + b) % 251;
}

unsigned char
sub(unsigned char a, unsigned char b)
{
	return (a - b) % 251;
}

unsigned char
mul(unsigned char a, unsigned char b)
{
	return (a * b) % 251;
}

unsigned char
calculate_inverse(unsigned char b)
{
	unsigned char i = 1;
	int rta = 0;
	while((rta = (b*i) %251) != 1)
	{
		++i;
	}
	return i;
}

unsigned char
divide(unsigned char a, unsigned char b)
{
	if(inverse[b] == 0)
	{
		inverse[b] = calculate_inverse(b);
	}
	return (a * inverse[b]) % 251;
}
