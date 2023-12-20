#include <stdio.h>

//At a time only one character can be stored in buffer
int buffer = -1; //-1 indicates empty buffer

//Push 1 character to input buffer
void ungetch (char c)
{
	if (buffer != -1)
		printf ("Buffer full\n");
	else
		buffer = c;
}

//Read a character
int getch ()
{
	if (buffer != -1)
	{
		int temp = buffer;
		buffer = -1;
		return temp;
	}
	else
		return getchar ();
}

int main ()
{
	char c = '*'; 

	//Move input character to buffer
	ungetch (c);

	while ((c = getch ()) != EOF)
		printf ("%c", c);

	return 0;
}
