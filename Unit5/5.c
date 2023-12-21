#include <stdio.h>

//Replicate the inbuilt strncat, strncpy and strncmp funtions

void str_ncpy (char *string1, char *string2, int n)
{
	while (n-- && (*string1++ = *string2++));
}

void str_ncat (char *string1, char *string2, int n)
{
	//Reach end of 1st string
	while (*string1++);
	string1--;

	//Write first n characters of string2 at the end of string1
	while (n-- && (*string1++ = *string2++));
}

int str_ncmp (char *string1, char *string2, int n)
{
	while (n-- && (*string1++ == *string2++));
	
	return (n == 0) || (*string1 - *string2);
}


int main ()
{
	char string1 [1000], string2 [1000];
	int n = 4;

	scanf ("%s", string1);
	scanf ("%s", string2);
	
	if (!str_ncmp (string1, string2, n))
		printf ("First n chars are same\n");
	else
		printf ("First n chars not same\n");

	str_ncpy (string1, string2, n);
	printf ("Copied first n characters: %s\n", string1);

	str_ncat (string1, string2, n);
	printf ("Concatenated string: %s\n", string1);
	return 0;
}
