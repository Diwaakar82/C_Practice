#include <stdio.h>

int main  ()
{
	int nb = 0, nl = 0, nt = 0;
	char c;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
			nb++;
		else if (c == '\n')
			nl++;
		else if (c == '\t')
			nt++;
	}
	printf( "Blanks: %d\nTabs: %d\nLines: %d\n", nb, nt, nl);
	return 0;
}	
