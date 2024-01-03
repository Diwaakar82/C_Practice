#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Modify pattern finding program to check in files

//Print line with pattern based on the options provided
void find_pattern (FILE *file_ptr, char *file_name, char *pattern, int options)
{
	char line [100];
	int line_number = 0;
	
	while (fgets (line, 100, file_ptr) != NULL)
	{
		line_number++;
		//Check if pattern exists and if the except flag is set
		if ((strstr (line, pattern) != NULL) != (options & 1))
		{
			printf ("%s-> ", file_name);
			if (options & 2)
				printf ("Line: %d ", line_number);
			printf ("%s", line);
		}
	}
}

int main (int argc, char *argv [])
{
	char pattern [100];
	int c, options = 0;
	FILE *file_ptr;
	
	//Handle options
	while (--argc > 0 && (*(++argv) [0] == '-'))
		while (c = *++argv [0])
			switch (c)
			{
				case 'x':
					options += 1;
					break;
				case 'n':
					options += 2;
					break;
				default:
					printf ("Invalid option\n");
					argc = 0;
					break;
			}
	
	//Read pattern
	if (argc >= 1)
		strcpy (pattern, *argv);
	else
	{
		printf ("Usage find -x -n pattern [file ...]\n");
		exit (0);
	}
	
	//Get input from cmd if no file provided
	if (argc == 1)
		find_pattern (stdin, "cmd", pattern, options);
	//Open file and read lines
	else
	{
		while (--argc)
		{
			//Couldn't open file
			if ((file_ptr = fopen (*++argv, "r")) == NULL)
			{
				fprintf (stderr, "Can't open file %s\n", *argv);
				exit (0);
			}
			else
			{
				find_pattern (file_ptr, *argv, pattern, options);
				fclose (file_ptr);
			}
		}
	}
	
	return 0;
}
