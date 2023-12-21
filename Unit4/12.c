#include <stdio.h>

//Implement itoa () using recursion

void itoa (int *i, int number, char number_str [])
{
	//Base case to exit when the number becomes 0
	if (!number)
		return;
	
	//Recursive call to reach the most significant bit
	itoa (i, number / 10, number_str);
	
	//If number is negative add - sign and change to positive
	if (number < 0)
	{
		if (!*i)
			number_str [(*i)++] = '-';
		number = -number;
	}

	//Write to string
	number_str [(*i)++] = (number % 10) + '0';
}

int main ()
{
	int number, i = 0;
	char number_str [100];
	scanf ("%d", &number);
	
	itoa (&i, number, number_str);

	printf ("Number converted to string: %s\n", number_str);
	return 0;
}
