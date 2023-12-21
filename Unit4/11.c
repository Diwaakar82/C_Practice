#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'


//Modify the given calculator program using a static variable to remove the need of ungetch
int stack_ptr = 0;
int buffer_ptr = 0;

double values [100];
char buffer [100];

//Read character from buffer
int getch (void) 
{ 
	return (buffer_ptr > 0) ? buffer [--buffer_ptr] : getchar (); 
}

//Get the next operator
int getop (char input_str [])
{
	int i, c;
	static char last_character = 0;
	
	if (!last_character)
		c = getch ();
	else
	{
		c = last_character;
		last_character = 0;
	}

	while ((input_str [0] = c) == ' ' || c == '\t')
		c = getch ();
	input_str [1] = '\0';
	
	//Return if found an operator
	if (!isdigit (c) && c != '.' && c != '-')
		return c;
	
	//If read character is - check if it's an unary or binary operator
	i = 0;
	if (c == '-')
	{
		if(isdigit (c = getch()) || c == '.')
            		input_str [++i] = c;
        	else
            	{
                	if (c != EOF)
				last_character = c;
                	return '-';
            	}
	}

	//Read number and store in the string
	if (isdigit (c))
		while (isdigit (input_str [++i] = c = getch ()));	
	if (c == '.')
		while (isdigit (input_str [++i] = c = getch ()));

	input_str [i] = '\0';
	if (c != EOF)
		last_character = c;
	return NUMBER;
}

//Add to stack
void push (double f)
{
	if (stack_ptr < 100)
		values [stack_ptr++] = f;
	else
		printf("error: stack full, can't push %g\n",f);
}

//Remove from stack
double pop (void)
{
	if (stack_ptr > 0)
		return values [--stack_ptr];
	else 
	{
		printf ("error: stack empty\n");
		return 0.0;
	}
}


int main ()
{
	int type;
	int operator2, operator1;
	char input_str [100];

	//Read input character by character
	while ((type = getop (input_str)) != EOF) 
	{
		switch (type) 
		{
			case NUMBER:						//Push to stack if a number
				push (atof (input_str));
				break;
			case '+':						//Add
				push (pop () + pop ());
				break;
			case '*':						//Multiply
				push (pop () * pop ());
				break;
			case '-':						//Subtract
				operator2 = pop ();				//Store operator2 as not commutative
				push (pop () - operator2);
				break;
			case '/':						//Divide
				operator2 = pop ();				//Same as subtraction
				if (operator2 != 0.0)				
					push (pop () / operator2);
				else
					printf ("Error: zero divisor\n");	
				break;
			case '%':						//Modulo
				operator2 = pop ();
				if (operator2 != 0.0)
                		{
					operator1 = pop ();
					if (operator1 > 0 && operator2 > 0)
						push (operator1 % operator2);
					else if (operator1 < 0 && operator2 > 0)
					{
						operator1 = -operator1;
						push ((operator2 - (operator1 % operator2)) % operator2);
					}
					else if (operator1 > 0 && operator2 < 0)
					{
						operator2 = -operator2;
						push (-((operator2 - (operator1 % operator2)) % operator2));
					}
					else
					{
						operator1 = -operator1;
						operator2 = -operator2;
						push (-(operator1 % operator2));
					}
				}
                		else
                			printf("Error: zero divisor\n");
                		break;
			case '\n':
				printf ("\t%.8g\n", pop ());
				break;
			default:
				printf("error: unknown command %s\n", input_str);
				break;
		}
	}
	return 0;
}
