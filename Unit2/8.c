#include <stdio.h>

int main ()
{
	printf ("%u, %u: %u", ~5, (~0 >> 1), (unsigned int) ~0 - (unsigned int)(~0 >> 1));	
	return 0;
}

