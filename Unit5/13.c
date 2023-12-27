#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Display only last n lines

//Getting input lines
int getlin (char input_str [], int lim)
{
	int c, i;

	for (i = 0; (c = getchar ()) != EOF && c != '\n'; i++)
		input_str [i] = c;
	if (c == '\n')
	{
		input_str [i] = c;
		i++;
	}
	
	input_str [i] = '\0';
	return i;
}

int main (int argc, char *argv [])
{ 
	char *ptr, *buffer, *buffer_end;
	char line [100], *lines [100];

	int no_of_lines, i;
	
	//Default no of lines
	if (argc == 1)
		no_of_lines = 10;
	
	//Fix inputted n value
	else if (argc == 2 && (*++argv) [0] == '-')
		no_of_lines = atoi (argv [0] + 1);

	//Error case where -n not used properly
	else
		printf ("Invalid usage of tail\n");

	//Handling invalid numbers
	if (no_of_lines < 1 || no_of_lines > 10)
		no_of_lines = 10;

	//Initializing pointers and allocating necessary space
	for (i = 0; i < 10; i++)
		lines [i] = NULL;
	if ((ptr = buffer = malloc (100 * 100)) == NULL)
		printf ("Error: not enough memory\n");

	buffer_end = buffer + 100 * 100;

	int first, last = 0, nlines = 0, length;

	//Storing each line in array of character pointers
	while ((length = getlin (line, 100)) > 0)
	{
		if (ptr + length + 1 >= buffer_end)
			ptr = buffer;
		lines [last] = ptr;
		
		strcpy (lines [last], line);
		if (++last >= 100)
			last = 0;
		
		ptr += length + 1;
		nlines++;
	}

	if (no_of_lines > nlines)
		no_of_lines = nlines;

	first = last - no_of_lines;

	if (first < 0)
		first += 100;
	
	//Printing last n lines
	for (i = first; no_of_lines-- > 0; i = (i + 1) % 100)
		printf ("%s", lines [i]);

	return 0;
}
