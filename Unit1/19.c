#include <stdio.h>
#define MAXLINE 1000

int getlin (char s [], int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar ()) != EOF && c != '\n'; ++i)
		s [i] = c;
	for (int j = 0; j < i / 2; j++)
	{
		int temp = s [j];
		s [j] = s [i - j - 1];
		s [i - j - 1] = temp;
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
		printf ("%s", line);
	printf ("\n");
	return 0;
}

