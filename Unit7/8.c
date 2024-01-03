#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//Print files with heading on each page

//Add heading and necessary blank lines
int heading (char *file_name, int page_number)
{
	int line_number = 3;
	
	fprintf (stdout, "\n\n");
	fprintf (stdout, "%s   Page:  %d\n", file_name, page_number);
	
	while (line_number++ < 5)
		fprintf (stdout, "\n");
	return line_number;
}
	
//Print file contents
void file_print (FILE *file_ptr, char *file_name)
{
	int line_number, page_number = 1;
	char line [100];
	
	line_number = heading (file_name, page_number++);
	
	while (fgets (line, 100, file_ptr))
	{
		if (line_number == 1)
		{
			fprintf (stdout, "\f");
			line_number = heading (file_name, page_number++);
		}
		
		fputs (line, stdout);
		if (++line_number > 63)
			line_number = 1;
	}
	
	fprintf (stdout, "\f");
}

int main (int argc, char *argv [])
{
	FILE *file_ptr;
	
	//Print standard input as no arguements are given
	if (argc == 1)
		file_print (stdin, "cmd");
	else
	{
		while (--argc)
		{
			if ((file_ptr = fopen (*++argv, "r")) == NULL)
			{
				fprintf (stderr, "Can't open file %s", *argv);
				exit (0);
			}
			else
			{
				file_print (file_ptr, *argv);
				fclose (file_ptr);
			}
		}
	}
	
	return 0;
}
