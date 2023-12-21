#include <stdio.h>

//Use macro to define swap function

#define swap(t, x, y) {t temp = x; x = y; y = temp;}

int main ()
{
	int a = 1, b = 2;
	printf ("Before swapping: a = %d, b = %d\n", a, b);

	//Gets replaced by the macro
	swap (int, a, b);

	printf ("After swapping: a = %d, b = %d\n", a, b);
	return 0;
}
