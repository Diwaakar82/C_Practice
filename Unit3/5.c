#include <stdio.h>
#define abs(x) ((x >= 0) ? x : -(x))
//Implement itob (number to string of given base).

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

//Convert given number to string of given base
void itob (int number, char output_num [], int base)
{
	int sign = (number < 0), i = 0;

	//Extract each digit an add to the string
	do
	{
		int digit = abs(number % base);
		output_num [i++] = (digit <= 9) ? digit + '0' : digit - 10 + 'a';
	}while (number /= base);

	//If the given number is negative add - symbol
	if (sign)
		output_num [i++] = '-';
	output_num [i] = '\0';
	reverse (output_num, i);
}

int main ()
{
	int number, base;
	scanf ("%d", &number);
	scanf ("%d", &base);
	char output_num [100];

	if (base > 36 || base < 2)
	{
		printf ("Base doesn't exist!!\n");
		return 0;
	}
	itob (number, output_num, base);
	printf ("Number as string in base %d: %s\n", base, output_num);
	
	return 0;
}

