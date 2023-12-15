#include <stdio.h>
#define MAXLINE 1000

int remove_trail (char s [])
{
	int len = 0;
	while (s [len++] != '\n');
	len--;

	while (len > 0 && (s [len] == ' ' || s [len] == '\t'))
		len--;
	//printf ("#%d\n", len);
	if (len > 0)
	{
		len++;
		s [len] = '\n';
		len++;
		s [len] = '\0';
	}
	return len;
}

int getlin (char s [], int lim)
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
	return i;
}


int main ()
{
	int len;
	char line [MAXLINE];

	while ((len = getlin (line, MAXLINE)) > 0)
	{
		if (remove_trail (line) > 0) 
			printf ("%s", line);
		//printf ("#");
	}
	//printf ("\n");
	return 0;
}

