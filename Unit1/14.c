#include <stdio.h>

int main  ()
{
	int flag = 0, chr [128];
	char c;
	
	for (int i = 0; i < 128; i++)	
		chr [i] = 0;

	while ((c = getchar()) != EOF)
		chr [c]++;
	
	for (int i = 0; i < 128; i++)
	{
		printf ("%c |  ", i);
		for (int j = 0; j < chr [i]; j++)
			printf ("X");
		printf ("\n");
	}
	return 0;
}	
