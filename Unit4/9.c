#include <stdio.h>

//Modify program to handle EOF character
int buffer_ptr = 0;
int buffer [1000]; 			//Using an integer typed buffer will help Handle EOF character as it has value -1

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

int main ()
{
	char c = '*';

	ungetch (c);

	while ((c = getch ()) != EOF)
		putchar (c);

	return 0;
}
