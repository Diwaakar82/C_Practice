#include <stdio.h>
#include <ctype.h>
#include <string.h>

//Compare two files and print the first line where they differ

//Comparing function
void lineCompare (FILE *file_pointer1, FILE *file_pointer2)
{
	char line1 [100], line2 [100];
	char *line_pointer1, *line_pointer2;
	
	do
	{
		//Read line by line of each file
		line_pointer1 = fgets (line1, 100, file_pointer1);
		line_pointer2 = fgets (line2, 100, file_pointer2);
		
		//Lines read in both files
		if (line_pointer1 == line1 && line_pointer2 == line2)
			if (strcmp (line1, line2))
			{
				printf ("Difference at line: \n%s\n%s", line1, line2);
				line_pointer1 = line_pointer2 = NULL;
			}
		//File 1 ended
		else if (line_pointer1 != line1 && line_pointer2 == line2)
			printf ("File 1 ends at line:\n%s", line1);
		//File 2 ended
		else if (line_pointer1 == line1 && line_pointer2 != line2)
			printf ("File 2 ends at line:\n%s", line2);
	}while (line_pointer1 == line1 && line_pointer2 == line2);
	
	//Both files ended
	if (line_pointer1 != line1 && line_pointer2 != line2)
		printf ("Same files\n");
}

int main (int argc, char *argv [])
{
	if (argc != 3)
		printf ("Invalid number of arguements\n");
	else
	{
		//Create pointers to each file
		FILE *file_pointer1, *file_pointer2;
		file_pointer1 = fopen (*++argv, "r");
		file_pointer2 = fopen (*++argv, "r");
		
		lineCompare (file_pointer1, file_pointer2);
	}
	return 0;
}
