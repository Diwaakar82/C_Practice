#include <stdio.h>

//Push the entire string into the input
int buffer_ptr = 0;
int buffer [1000];

//Push 1 character to input buffer
void ungetch (char c)
{
	if (buffer_ptr > 1000)
		printf ("Too many characters!!!\n");
	else
		buffer [buffer_ptr++] = c;
}

//Get one character
int getch ()
{
	return (buffer_ptr > 0) ? buffer [--buffer_ptr] : getchar ();
}

//Push entire string to input buffer
void ungets (char input_str [], int length)
{
	int i = length;
	
	while (length--)
		ungetch (input_str [--i]);
}

int main ()
{
	char input [1000], c;
	int i = 0;
	
	//Get input string
	while (i < 1000 && (c = getchar ()) != EOF && c != '\n')
		input [i++] = c;

	if (c == '\n')
		input [i++] = c;
	input [i] = '\0';

	ungets (input, i);

	while ((c = getch ()) != EOF)
		putchar (c);

	return 0;
}
