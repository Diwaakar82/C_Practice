#include <stdio.h>

unsigned setbits (unsigned x, int p, int n, unsigned y)
{
	return x & ~(~((~0 << n)) << (p + 1 - n)) | (y & ~(~0 << n) << (p + 1 - n));
}
int main ()
{
	unsigned x = 213, y = 217;
	int p = 4, n = 4;
	printf ("Changed: %u to %u\n", x, setbits (x, p, n, y));
	return 0;
}
