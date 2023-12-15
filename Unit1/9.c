#include <stdio.h>

int main  ()
{
	int flag = 0;
	char c;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
		{
			if (!flag)
			{
				printf ("%c", c);
				flag = 1;
			}
		}
		else
		{
			printf ("%c", c);
			flag = 0;
		}
	}
	return 0;
}	
