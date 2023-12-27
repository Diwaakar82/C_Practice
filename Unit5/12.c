#include <stdio.h>
#include <stdlib.h>

//Modify entab to take parameters -m (starting column number) +n (gap between tabstops)

int tab_position (int position, char *tabs)
{
	if (position > 100)
		return 1;
	else
		return 0;
}

//Use an array to set 1 or 0 based on if its a tabstop
void esettab (int argc, char *argv [], char *tabs)
{
	int i, increement, position;
	
	//Default tabstops if no arguements provided
	if (argc <= 1)
		for (i = 1; i <= 100; i++)
			if (i % 8 == 0)
				tabs [i] = 1;
			else
				tabs [i] = 0;

	//Parameters passed in -m, +n format
	else if (argc == 3 && *argv [1] == '-' && *argv [2] == '+')
	{
		position = atoi (&(*++argv) [1]);
		increement = atoi (&(*++argv) [1]);

		for (i = 1; i <= 100; i++)
			if (i != position)
				tabs [i] = 0;
			else
			{
				tabs [i] = 1;
				position += increement;
			}
	}

	//Explicitly provided tabstops
	else
	{
		for (i = 1; i <= 100; i++)
			tabs [i] = 0;

		while (--argc > 0)
		{
			position = atoi (*++argv);
			if (position > 0 && position <= 100)
				tabs [position] = 1;
		}
	}
}

void entab (char *tabs)
{
	int c, position;
	int no_of_blanks = 0, no_of_tabs = 0;

	for (position = 1; (c = getchar ()) != EOF; position++)
	{
		if (c == ' ')
		{
			if (!tab_position (position, tabs))
				no_of_blanks++;
			else
			{
				no_of_blanks = 0;
				no_of_tabs++;
			}
		}
		else
		{
			for (; no_of_tabs > 0; no_of_tabs--)
				printf ("\t");
			if (c == '\t')
				no_of_blanks = 0;
			else
				for (; no_of_blanks > 0; no_of_blanks--)
					printf (" ");
			printf ("%c", c);
			
			if (c == '\n')
				position = 0;
			else if (c == '\t')
				while (!tab_position (position, tabs))
					position++;
		}
	}
}

int main (int argc, char *argv [])
{
	char tabs [100];
	esettab (argc, argv, tabs);
	entab (tabs);

	return 0;
}
