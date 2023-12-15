#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getlin (char s [], int lim)
{
	int c, i;
	strcpy (s, "");
	for (i = 0; i < lim - 1 && (c = getchar ()) !=EOF && c != '\n'; ++i)
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

void copy (char to [], char from [])
{
	int i = 0;

	while ((to [i] = from [i]) != '\0')
		++i;
}

int main ()
{
	int len;
	int max;
	char line [MAXLINE];
	char longest [MAXLINE];

	max = 0;
	while ((len = getlin (line, MAXLINE)) > 0)
	{
		if (len > max) 
		{
			max = len;
			copy (longest, line);
		}
		printf ("\n");
	}
	if (max > 0)
		printf ("\n%s", longest);
	printf ("\n");
	return 0;
}

