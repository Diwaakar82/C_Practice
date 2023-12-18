#include <stdio.h>

//Rotate number by n bits
//
//Find word length
int noOfBits ()
{
	unsigned int v = (unsigned)~0;
	
	int i = 0;
	while (v > 0)
	{
		v >>= 1;
		i++;
	}
	return i;
}

//Right rotate
unsigned int rightRotate (int num, int n)
{
	unsigned int rightbits;
	int length = noOfBits ();
	//printf ("Word length: %d\n", length);

	rightbits = num << (length - n);
	num >>= n;
	num |= rightbits;

	return num;
}

int main ()
{
	int num, n;
	printf ("Enter a number: ");
	scanf ("%d", &num);
	printf ("\nEnter no of bits to be shifted: ");
	scanf ("%d", &n);
	
	printf ("Right rotated number: %u\n", rightRotate (num, n));
	return 0;
}
