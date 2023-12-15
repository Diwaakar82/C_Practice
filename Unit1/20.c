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
		if (s [j] == '\t')
		{
			int nxt_tb_stp = (cnt + tablen) / tablen;
			int spaces = nxt_tb_stp * tablen - cnt;
			cnt += spaces;
			while (spaces--)
				printf (" ");
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

