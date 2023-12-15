#include <stdio.h>

int main  ()
{
	char c;

	while ((c = getchar()) != EOF)
	{
		if (c == '\\')
			printf ("\\\\");
		else if (c == '\t')
			printf ("\\t");
		else if (c == '\b')
			printf ("\\b");
		else
			printf ("%c", c);
	}
	return 0;
}	


//Sample test cases:
// facdsv      dfsvsd
//fdsfd		 	,cl;ds

