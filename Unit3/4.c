#include <stdio.h>
#define abs(x) ((x >= 0) ? x : -x)
//Implement itoa (number to string) which handles the largest negative number.

//Function to reverse the given string
void reverse (char input_str [], int length)
{
	for (int i = 0; i < length / 2; i++)
	{
		char temp = input_str [i];
		input_str [i] = input_str [length - i - 1];
		input_str [length - i - 1] = temp;
	}
}

//Convert given number to string
void itoa (int number, char output_num [])
{
	int sign = (number < 0), i = 0;

	//Extract each digit an add to the string
	do
	{
		output_num [i++] = abs(number % 10) + '0';
	}while (number /= 10);

	//If the given number is negative add - symbol
	if (sign)
		output_num [i++] = '-';
	output_num [i] = '\0';
	
	//printf ("\nBefore rev: %s\n", output_num);
	reverse (output_num, i);
}

int main ()
{
	int number;
	scanf ("%d", &number);
	
	char output_num [100];
	itoa (number, output_num);
	printf ("Number as string: %s\n", output_num);
	return 0;
}

