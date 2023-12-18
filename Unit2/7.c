#include <stdio.h>

unsigned invert (unsigned x, int p, int n)
{
	return x ^ (~(~0 << n) << (p + 1 - n));
}
int main ()
{
	unsigned x = 8;
	int p = 3, n = 3;
	printf ("Changed: %u to %u\n", x, invert (x, p, n));
	return 0;
}
