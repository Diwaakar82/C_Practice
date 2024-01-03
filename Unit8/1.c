#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <stdarg.h>

//Rewrite cat using open, close, read, write system calls

//Prints error message
void error (char *fmt, ...)
{
	va_list args;
	
	va_start (args, fmt);
	fprintf (stderr, "Error: ");
	vfprintf (stderr, fmt, args);
	fprintf (stderr, "\n");
	va_end (args);
	
	exit (0);
}

//Copies contents of file 1 to file 2
void filecopy (int input_file_descriptor, int output_file_descriptor)
{
	int n;
	char buffer [100];
	
	//Read from iput file into the buffer and writes to the output file
	while ((n = read (input_file_descriptor, buffer, 100)) > 0)
		if (write (output_file_descriptor, buffer, n) != n)
			error ("Write error\n");
}

int main (int argc, char *argv [])
{
	int file_descriptor;
	
	//Copy standard input
	if (argc == 1)
		filecopy (0, 1);
	else
		while (--argc)
			if ((file_descriptor = open (*++argv, O_RDONLY)) == -1)
				error ("Can't open file %s", *argv);
			else
			{
				filecopy (file_descriptor, 1);
				close (file_descriptor);
			}	
	
	return 0;
}
