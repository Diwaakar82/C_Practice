#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv [])
{
	int c;
	
	if (!strcmp (argv [1], "lower"))
		while ((c = getchar ()) != EOF)
			putchar (tolower (c));
	else if (!strcmp (argv [1], "upper"))
		while ((c = getchar ()) != EOF)
			putchar (toupper (c));
	else
		printf ("Not defined\n");
		
	return 0;
}
