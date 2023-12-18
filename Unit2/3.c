#include <stdio.h>
#include <ctype.h>

//Program to convert hexadecimal string to decimal equivalent.
int htoi (char str [], int length)
{
	int num = 0, i = 0;

	//Skip 0x or 0X at the beginning
	if (str [i] == '0')
		i += 2;

	//Read character by character and compute the value
	while (i < length)
	{
		if (str [i] >= '0' && str [i] <= '9')
			num = 16 * num + str [i] - '0';   
		else
			num = 16 * num + tolower (str [i]) - 'a' + 10;   // Plus 10 as a is 10 in hexadecimal
		i++;
	}
	return num;
}

int main ()
{
	char str [1000], input;
	int i = 0;

	//Get string input
	while ((input = getchar ()) != EOF && input != '\n')
		str [i++] = input;
	
	printf ("\nInteger value of %s: %d\n", str, htoi (str, i));
	return 0;
}
