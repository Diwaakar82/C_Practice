#include <stdio.h>

//Find the rightmost position of the occurance of string 2 in string 1

int strrindex (char string1 [], char string2 [])
{
	int right_most_index = -1;
	for (int i = 0; string1 [i] != '\0'; i++)
	{
		int j = i, k = 0;
		while (string1 [j] != '\0' && string2 [k] != '\0' && string1 [j++] == string2 [k++]);
		
		if (k && string2 [k] == '\0')
			right_most_index = i;		
	}
	return right_most_index;

}

int main ()
{
	char string1 [100], string2 [100];
	scanf ("%s", string1);
	//getchar ();
	scanf ("%s", string2);
	
	int index = strrindex (string1, string2);
	printf ("Rightmost matching index: %d\n", index);

	return 0;
}
