#include <stdio.h>
#include <ctype.h>

//Modify the getint function to handle number not following + or - properly
char buffer [1000];
int buffer_ptr = 0;

//Get from buffer of cmd
int getch() 
{
    return (buffer_ptr > 0) ? buffer [--buffer_ptr] : getchar ();
}

//Store in buffer
void ungetch (int c) 
{
    if (buffer_ptr >= 1000)
        printf ("ungetch: too many characters\n");
    else
        buffer [buffer_ptr++] = c;
}

//Read and number and store in the array
int getint (int *number)
{
	int c, sign;

	//Skip blanks
	while (isspace (c = getch()));

	//Return invalid if not a number
	if (!isdigit (c) && c != EOF && c != '+' && c != '-') 
	{
		ungetch (c);
		return -1;
	}
	
	//Store sign
	sign = (c == '-') ? -1 : 1;

	//Read + or -
	if (c == '+' || c == '-' )
		c = getch();
	
	//Return 0 if next char isnt a number
	if (!isdigit (c))
		return 0;

	//Read consecutive numbers
	for (*number = 0; isdigit (c); c = getch ())
		*number = 10 * *number + (c - '0');

	//Change sign
	*number *= sign;
	if (c != EOF)
		ungetch (c);
	return c;
}

int main ()
{
	int i, length = 0, numbers [1000], getint (int *);
	
	//Read characters one by one and call the getint function
	while (length < 1000 && getint (&numbers [length]) != EOF)
		if (numbers [length])
			length++;
	
	//Print the stored numbers
	printf ("\nStored numbers:\n");
	for (i = 0; i <= length; i++)
		printf ("%d ", numbers [i]);
	printf ("\n");
	return 0;
}
