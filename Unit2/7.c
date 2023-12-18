#include <stdio.h>

//Write a function invert(x,p,n)
//that returns x with the n bits
//that begin at position p inverted (i.e., I changed into 0 and vice versa), leaving
//the others unchanged.
int invert (int x, int p, int n)
{
	return x ^ (~(~0 << n) << (p + 1 - n));  //Use XOR with 1s to invert the corresponding bits
}

int main ()
{
	int x = 500;
	int p = 4, n = 2;
	printf ("Changed: %u to %u\n", x, invert (x, p, n));
	return 0;
}
