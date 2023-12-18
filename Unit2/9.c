#include <stdio.h>

//Optimize the given bitcount function using x & (x - 1) property.
unsigned int bitcount (int num)
{
	int count = 0;
	
	while (num > 0)
	{
		count++;
		num &= num - 1;
	}

	return count;
}
int main ()
{
	int num;
	scanf ("%d", &num);

	printf ("\nNumber of set bits: %d\n", bitcount (num));
	return 0;
}
