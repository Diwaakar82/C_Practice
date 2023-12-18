#include <stdio.h>

//Remove common characters of two strings from the 1st string
void squeeze (char str1 [], char str2 [], int length1, int length2)
{
	int counter [128] = {0};   //Counter to find count of each character
	int i = 0;

	while (i < length1)
		counter [str1 [i++]] = 1;
	
	i = 0;
	while (i < length2)
		counter [str2 [i++]] = 0;

	i = 0;
	int k = 0;
	while (i < length1)
	{
		if (counter [str1 [i]])
			str1 [k++] = str1 [i];
		i++;
	}
	str1 [k] = '\0';
}

//Getting the input string
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

	squeeze (str1, str2, length1, length2);
	printf ("Squeezed string: %s\n", str1);
	return 0;
}
