#include <stdio.h>
#include <ctype.h>

//Write a getfloat function to handle floating point numbers
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
int getfloat (float *number)
{
	int c, sign;
	float power;

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
	
	if (c == '.')
		c = getch ();
	
	//calculate the fractional part
	for (power = 1; isdigit (c); c = getch ())
	{
		power *= 10;
		*number = 10 * *number + (c - '0');
	}

	//Change sign and convert number to decimal form
	*number *= sign;
	*number /= power;

	if (c != EOF)
		ungetch (c);
	return c;
}

int main ()
{
	int i, length = 0;
	float numbers [1000];
	
	//Read characters one by one and call the getfloat function
	while (length < 1000 && getfloat (&numbers [length]) != EOF)
		if (numbers [length])
			length++;
	
	//Print the stored numbers
	printf ("\nStored numbers:\n");
	for (i = 0; i <= length; i++)
		printf ("%f ", numbers [i]);
	printf ("\n");
	return 0;
}
