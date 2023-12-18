#include <stdio.h>

//Write a function setbits(x,p,n,y) that returns x with the n 
//bits that begin at position p set to the rightmost n bits of y, leaving the other
//bits unchanged.
int setbits (int x, int p, int n, int y)
{
	return x & ~(~(~0 << n) << (p + 1 - n)) | ((y & ~(~0 << n)) << (p + 1 - n));
}

int main ()
{
	int x = 213, y = 217;
	int p = 4, n = 4;
	printf ("Changed: %d to %d\n", x, setbits (x, p, n, y));
	return 0;
}
