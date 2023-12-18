#include <stdio.h>

//Find first common character between the given two strings
int any (char str1 [], char str2 [], int length1, int length2)
{
	int char_check [128] = {0}; //Mark presence of presence of characters available in the 2nd string 
	int i = 0;

	while (i < length2)
		char_check [str2 [i++]] = 1;

	i = 0;
	while (i < length1)
		if (char_check [str1 [i]])
			return i;
		else
			i++;

	return -1;
}

//Getting input string
int getlin (char str [])
{
	int i = 0;
	char input;

	while ((input = getchar ()) != EOF && input != '\n')
		str [i++] = input;

	return i;
}

int main ()
{
	char str1 [1000], str2 [1000];
	int length1 = getlin (str1);
	int length2 = getlin (str2);

	printf ("First common character: %d\n", any (str1, str2, length1, length2));
	return 0;
}
