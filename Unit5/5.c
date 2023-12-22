#include <stdio.h>

//Replicate the inbuilt strncat, strncpy and strncmp funtions

//Copy first n characters of string2 to string1
void str_ncpy (char *string1, char *string2, int n)
{
	while (n-- && (*string1++ = *string2++));
}

//Add first n characters of string2 to the end of string1
void str_ncat (char *string1, char *string2, int n)
{
	//Reach end of 1st string
	while (*string1++);
	string1--;

	//Write first n characters of string2 at the end of string1
	while (n-- && (*string1++ = *string2++));
}

//Compare the first n characters of both strings
int str_ncmp (char *string1, char *string2, int n)
{
	while (--n && (*string1++ == *string2++));
	
	*string1--;
	*string2--;	
	if (!n && (*string1 == *string2))
		return 0;
	else
		return *(string1) - *(string2);
}


int main ()
{
	char string1 [1000], string2 [1000];
	int n = 4, result;

	scanf ("%s", string1);
	scanf ("%s", string2);
	
	result = str_ncmp (string1, string2, n);
	if (!result)
		printf ("First n chars are same\n");
	else
		printf ("First n chars not same %d\n", result);

	str_ncpy (string1, string2, n);
	printf ("Copied first n characters: %s\n", string1);

	str_ncat (string1, string2, n);
	printf ("Concatenated string: %s\n", string1);
	return 0;
}
