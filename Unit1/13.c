#include <stdio.h>

int main  ()
{
	int flag = 0, lengths [10], len = 0;
	char c;
	
	for (int i = 0; i < 10; i++)	
		lengths [i] = 0;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
		{
			if (!flag)
			{
				lengths [len]++;
				len = 0;
				flag = 1;
			}
		}
		else
		{
			len++;
			flag = 0;
		}
	}
	
	lengths [len - 1]++;
	for (int i = 0; i < 10; i++)
	{
		printf ("%d |  ", i);
		for (int j = 0; j < lengths [i]; j++)
			printf ("X");
		printf ("\n");
	}
	return 0;
}	
