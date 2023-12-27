#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER 'n'

//Reverse polish calculator using command line arguements
char buffer [1000];
double values [1000];
int buffer_ptr = 0, stack_ptr = 0;

//Insert number into stack
void push (double number)
{
	if (stack_ptr < 1000)
		values [stack_ptr++] = number;
	else
		printf ("Stack full\n");
}

//Remove element from stack
double pop ()
{
	if (stack_ptr)
		return values [--stack_ptr];
	else
		printf ("Stack empty\n");
	return 0;
}

//Store character in buffer
void ungetch (int c)
{
	if (buffer_ptr >= 1000)
		printf ("Buffer full\n");
	else
		buffer [buffer_ptr++] = c;
}

//Read character from buffer or input
int getch ()
{
	return (buffer_ptr > 0) ? buffer [--buffer_ptr] : getchar ();
}

//Store string in buffer
void ungets (char input_str [])
{
	int len = strlen (input_str);

	while (len)
		ungetch (input_str [--len]);
}

//Get next operator or integral part
int getop (char input_str [])
{
	int i, c;
	
	//Skip blanks
	while ((input_str [0] = c = getch ()) == ' ' || c == '\t');
	input_str [1] = '\0';
	
	if (!isdigit (c) && c != '.')
	{
		printf ("(%c)\n", c);
		return c;
	}
	
	//Read the number
	i = 0;
	if (isdigit (c))
		while (isdigit (input_str [++i] = c = getch ()));

	//Read fractional part
	if (c == '.')
		while (isdigit (input_str [++i] = c = getch ()));
	input_str [i] = '\0';

	if (c != EOF)
		ungetch (c);
	return NUMBER;
}

int main (int argc, char *argv [])
{
	char input_str [1000];
	double operand2;
	
	values [0] = 8;
	
	while (--argc)
	{
		ungets (" ");

		//Read the string arguements passed
		ungets (*++argv);

		switch (getop (input_str))
		{
			case NUMBER:
				push (atof (input_str));
				break;
			case '+':
				push (pop () + pop ());
				break;
			case '*':
				push (pop () * pop ());
				break;
			case '-':
				operand2 = pop ();
				push (pop () - operand2);
				break;
			case '/':
				operand2 = pop ();
				if (operand2)
					push (pop () / operand2);
				else
					printf ("Can't divide by 0\n");
				break;
			default:
				printf ("Unknown command: %s\n", input_str);
				argc = 1;
				break;
		}
	}

	printf ("Soln: %g\n", pop ());
	return 0;
}

