#include <stdio.h>

//Replicate the inbuilt strend funtion

int str_end (char *string1, char *string2)
{
	int length = 0;
	//Reach end of 1st string
	while (*string1++);
	string1--;
	
	//Reach end of 2nd string and obtain its length
	while (*string2++)
		length++;
	string2--;

	//Check if contents of string2 exists at the end of string1
	while (length > 0 && *string1-- == *string2--)
		length--;
	
	if (!length)
		return 1;
	else
		return 0;
}

int main ()
{
	char string1 [1000], string2 [1000];

	scanf ("%s", string1);
	scanf ("%s", string2);

	if (str_end (string1, string2))
		printf ("String2 suffixes string1\n");
	else
		printf ("String2 does not suffix string1\n");

	return 0;
}
