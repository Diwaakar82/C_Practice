#include <stdio.h>

//Replicate the inbuilt strcat funtion

void str_cat (char *string1, char *string2)
{
	//Reach end of 1st string
	while (*string1++);
	string1--;

	//Write contents of string2 at the end of string1
	while (*string1++ = *string2++);
}

int main ()
{
	char string1 [1000], string2 [1000];

	scanf ("%s", string1);
	scanf ("%s", string2);

	str_cat (string1, string2);

	printf ("Concatenated strings: %s\n", string1);
	return 0;
}
