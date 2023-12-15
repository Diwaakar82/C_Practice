#include <stdio.h>

int main ()
{
	char c;
	c = getchar ();
	while ((c = getchar ()) != EOF)
		printf ("%d", c != EOF);
	printf ("%d\n", c != EOF);
	return 0; 
}
