#include <stdio.h>
#include <ctype.h>
//Print non graphic characters in octel and break long lines

//Increement position counter for output
int inc (int position, int n)
{
	if (position + n < 20)
		return position + n;
	else
	{
		putchar ('\n');
		return n;
	}
}

int main ()
{
	int c, position = 0;
	
	while ((c = getchar ()) != EOF)
	{
		if (iscntrl (c) || c == ' ')
		{
			position = inc (position, 6);
			printf (" \\%03o ", c);
			
			if (c == '\n')
			{
				position = 0;
				putchar ('\n');
			}
		}
		else
		{
			position = inc (position, 1);
			putchar (c);
		}
	}
	
	return 0;
}
