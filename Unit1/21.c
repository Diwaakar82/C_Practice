#include <stdio.h>
#define MAXLINE 1000

int getlin (char s [], int lim, int tablen)
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
	
	int cnt = 0;
	for (int j = 0; j < i; j++)
	{
		if (s [j] == ' ')
		{
			int next_char = j + 1;
			while (s [next_char] == ' ')
			{
				next_char++;
				if (next_char % tablen == 0)
				{
					printf ("\t");
					j = next_char;
				}
			}
			for (int k = j + 1; k <= next_char; k++)
				printf (" ");
			j = next_char - 1;
		}
		else
		{
			printf ("%c", s [j]);
			cnt++;
		}
	}
	return i;
}

int main ()
{
	int len, ntabstops = 100;
	int tablen = MAXLINE / ntabstops;
	char line [MAXLINE];

	while ((len = getlin (line, MAXLINE, tablen)) > 0);
	printf ("\n");
	return 0;
}

