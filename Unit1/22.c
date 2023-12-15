#include <stdio.h>
#define MAXLINE 1000

int getlin (char s [], int lim, int foldlen)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar ()) != EOF && c != '\n'; ++i)
		s [i] = c;
	
	if (c == '\n') 
	{
		s [i] = c;
		++i;
	}
	s [i] = '\0';
	
	int space = -1, j = 0, k = 0;
	
	while (j < i)
	{
		if (s [j] == ' ')
			space = j;
		if (k == foldlen)
		{
			if (space == -1)
			{
				printf ("%c\n", s [j++]);
				k = 0;
				continue;
			}
			j = space + 1;
			k = 0;
			printf ("\n");
		}
		else
		{
			printf ("%c", s [j]);
			j++;
			k++;
		}
	}
	
	return i;
}

int main ()
{
	char line [MAXLINE];
	int foldlen = 20, len;
	while ((len = getlin (line, MAXLINE, foldlen)) > 0);
	printf ("\n");
	return 0;
}

