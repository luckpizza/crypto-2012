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
	int rta = (a + b) % 251;
	return rta;
}

unsigned char
sub(unsigned char a, unsigned char b)
{
	int rta = 0;
	if(a > b)
		return (a-b) % 251;
	rta = a -b;
	rta = (rta + 251)%251;
	return rta;
//	int rta;
//	int x = a;
//	rta =  (x - b) % 251;
//	return rta;
}

unsigned char
mul(unsigned char a, unsigned char b)
{
	unsigned char  rta = (a * b) % 251;
	return rta;
}

unsigned char
calculate_inverse(unsigned char b)
{
	if(b == 0 || b == 251)
		return 0;
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
	if(b == 0)
	{
		printf("Dividing by 0!!\n");
	}
	int rta = 0;
	if(inverse[b] == 0)
	{
		inverse[b] = calculate_inverse(b);
	}
	rta =  (a * inverse[b]) % 251;
	return rta;
}
