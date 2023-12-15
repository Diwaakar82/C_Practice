#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getlin (char s [], int lim)
{
	int c, i;
	strcpy (s, "");
	for (i = 0; i < lim - 1 && (c = getchar ()) != EOF && c != '\n'; ++i)
		s [i] = c;
	if (c != EOF)
	{
		while ((c = getchar ()) != EOF)
			i++;
	}
	if (c == '\n') 
	{
		s [i] = c;
		++i;
	}
	s [i] = '\0';
	return i;
}


int main ()
{
	int len;
	int max;
	char line [MAXLINE];
	char longest [MAXLINE];

	while ((len = getlin (line, MAXLINE)) > 0)
	{
		if (len > 80) 
			printf ("%s", line);
		printf ("\n");
	}
	printf ("\n");
	return 0;
}

