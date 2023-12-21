#include <stdio.h>
#include <ctype.h>

char buffer [1000];
int buffer_ptr = 0;

int getch() 
{
    return (buffer_ptr > 0) ? buffer [--buffer_ptr] : getchar ();
}


void ungetch (int c) 
{
    if (buffer_ptr >= 1000)
        printf ("ungetch: too many characters\n");
    else
        buffer [buffer_ptr++] = c;
}

int getint (int *pn)
{
	int c, sign;
	while (isspace (c = getch()));

	if (!isdigit (c) && c != EOF && c != '+' && c != '-') 
	{
		ungetch (c);
		return -1;
	}
	
	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-' )
		c = getch();

	if (!isdigit (c))
		return 0;

	for (*pn = 0; isdigit (c); c = getch ())
		*pn = 10 * *pn + (c - '0');

	*pn *= sign;
	if (c != EOF)
		ungetch (c);
	return c;
}

int main ()
{
	int i, length = 0, numbers [1000], getint (int *);

	while (length < 1000 && getint (&numbers [length]) != EOF)
		if (numbers [length])
			length++;

	printf ("\nStored numbers:\n");
	for (i = 0; i <= length; i++)
		printf ("%d ", numbers [i]);
	printf ("\n");
	return 0;
}
