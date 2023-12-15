#include <stdio.h>

int main ()
{
	char c, s [1000];
	int len = 0, isCmt = 0, isStr = 0;
	int nc = 0, nb = 0, ns = 0;

	while (len < 1000 && (c = getchar ()) != EOF)
		s [len++] = c;
	s [len] = '\0';

	for (int i = 0; i < len; i++)
	{
		if (isStr)
		{
			if (s [i] == '\"')
				isStr = 0;
		}
		else if (!isCmt)
		{
			if (s [i] == '\"')
			{
                		isStr = 1;
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
			{
				switch (s [i])
				{
					case '(':
						nb++;
						break;
					case ')':
						nb--;
						break;
					case '{':
						nc++;
						break;
					case '}':
						nc--;
						break;
					case '[':
						ns++;
						break;
					case ']':
						ns--;
				}
			}
		}
		else if (isCmt == 1)
		{
			if (s [i] == '\n')
				isCmt = 0;
		}
		else
		{
			if (s [i] == '*' && i + 1 < 1000 && s [i + 1] == '/')
				isCmt = 0;
		}
	}

	if (!ns && !nb && !ns)
		printf ("No errors\n");
	else
		printf ("There are errors\n");
	return 0;
}
