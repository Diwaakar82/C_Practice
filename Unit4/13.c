#include <stdio.h>

//Reverse the given string using recursion

void reverse (int i, int *length, char string [])
{
	//Base case: execute only till half the length of string
	if (i >= *(length) / 2)
		return;

	char temp = string [i];
	string [i] = string [*length - i - 1];
	string [*length - i - 1] = temp;

	//Recursive call
	reverse (i + 1, length, string);
}

int main ()
{
	int length = 0;
	char string [1000];

	scanf ("%s", string);
	
	//Compute string length
	while (string [length++] != '\0');
	length--;		//Input takes \n as extra character

	reverse (0, &length, string);

	printf ("Reversed string: %s\n", string);
	return 0;
}
