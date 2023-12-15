#include <stdio.h>

int main ()
{
	char c, s [1000];
	int len = 0, isCmt = 0, isStr = 0;

	while (len < 1000 && (c = getchar ()) != EOF)
		s [len++] = c;
	s [len] = '\0';
	printf ("#%s", s);
	
	for (int i = 0; i < len; i++)
	{
		if (isStr)
		{
			if (s [i] == '\"')
				isStr = 0;
			printf ("%c", s [i]);
		}
		else if (!isCmt)
		{
			if (s [i] == '\"')
			{
                		isStr = 1;
				printf ("%c", s [i]);
				continue;
			}
			if (s [i] == '/' && i + 1 < 1000)
			{
				if (s [i + 1] == '/')
					isCmt = 1;
				else if (s [i + 1] == '*')
					isCmt = 2;
			}
			else if (!isCmt)
				printf ("%c", s [i]);
		}
		else if (isCmt == 1)
		{
			if (s [i] == '\n')
				isCmt = 0;
			printf ("\n");
		}
		else
		{
			if (s [i] == '*' && i + 1 < 1000 && s [i + 1] == '/')
				isCmt = 0;
		}
		//printf ("%c", s [i])
	}
	return 0;
}
