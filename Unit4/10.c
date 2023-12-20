#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define NUMBER '0'
#define NAME 'n'

//Modify the given calculator program to take input as a whole string to remove neccesity of input buffer
int stack_ptr = 0;
int ptr = 0;

double values [100];
char input_line [100];

//Get input line
int getlin (char input_str [])
{
	int i = 0;
	char c;

	while ((c = getchar ()) != EOF && c != '\n')
		input_str [i++] = c;

	if (c == '\n')
		input_str [i++] = c;

	input_str [i] = '\0';

	return i;
}

//Get the next operator
int getop (char input_str [])
{
	int i, c;
	
	//Read a new line if the current line has been traversed fully
	if (input_line [ptr] == '\0')
	{
		if (getlin (input_line))
			ptr = 0;
		else
			return EOF;
	}
	
	//Skip leading spaces
	while ((input_str [0] = c = input_line [ptr++]) == ' ' || c == '\t');
	input_str [1] = '\0';
	
	//Read characters and return them to do corresponding operations
	i = 0;
	if (!isdigit (c))
	{
		while (isalpha (input_str [++i] = c = input_line [ptr++]) && c != ' ')
			tolower (input_str [i]);
		

		input_str [i] = '\0';
		if (c != EOF)
			ptr--;

		if (strlen (input_str) > 1)
			return NAME;
		else
			return input_str [0];
	}

	//Return if found an operator
        if (!isdigit (c) && c != '.' && c != '-')
                return c;
		
	//If read character is - check if it's an unary or binary operator
	if (c == '-')
	{
		if(isdigit (c = input_line [ptr++]) || c == '.')
            		input_str [++i] = c;
        	else
		{
			if (c != EOF)
				ptr--;
                	return '-';
		}
	}

	//Read number and store in the string
	if (isdigit (c))
		while (isdigit (input_str [++i] = c = input_line [ptr++]));	
	if (c == '.')
		while (isdigit (input_str [++i] = c = input_line [ptr++]));

	input_str [i] = '\0';
	if (c != EOF)
		ptr--;
	return NUMBER;
}

//Add to stack
void push (double f)
{
	if (stack_ptr < 100)
		values [stack_ptr++] = f;
	else
		printf("Error: stack full, can't push %g\n",f);
}

//Remove from stack
double pop (void)
{
	if (stack_ptr > 0)
		return values [--stack_ptr];
	else 
	{
		printf ("Error: stack empty\n");
		return 0.0;
	}
}

//Print top of stack
void show ()
{
	if (stack_ptr > 0)
		printf ("Top of the stack contains: %lf\n", values [stack_ptr - 1]);
	else
		printf ("Error: Stack empty\n");
}

//Duplicate top of stack
void duplicate ()
{
	if (stack_ptr > 0)
	{
		values [stack_ptr] = values [stack_ptr - 1];
		stack_ptr++;
	}
	else
		printf ("Error: Stack empty\n");
}

//Swap the top two numbers
void swap ()
{
	double number2 = pop (), number1 = pop ();
	push (number2);
	push (number1);
}

//Empty the stack
void clear ()
{
	stack_ptr = 0;
}

//Perform mathematical operations
void math_operation (char input_str [])
{
	if (!strcmp (input_str, "sin"))
		push (sin (pop ()));
	else if (!strcmp (input_str, "cos"))
                push (cos (pop ()));
	else if (!strcmp (input_str, "tan"))
                push (tan (pop ()));
	else if (!strcmp (input_str, "exp"))
                push (exp (pop ()));
	else if (!strcmp (input_str, "pow"))
        {
		double operand2 = pop ();
		push (pow (pop (), operand2));
	}
	else
		printf ("Error: %s not supported\n", input_str);
}

int main ()
{
	int type, variable = 0;
	int operator2, operator1;
	char input_str [100];
	double variables [26] = {0.0};

	//Read input character by character
	while ((type = getop (input_str)) != EOF) 
	{
		switch (type) 
		{
			case NUMBER:						//Push to stack if a number
				push (atof (input_str));
				break;
			case NAME:						//Perform corresponding math operation
				math_operation (input_str);
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
			case '=':
				pop ();
				if (variable >= 'A' && variable <= 'Z')
					variables [variable - 'A'] = pop ();
				else
					printf ("Error: Invalid variable\n");
				break;
			case 'p':						//Print the top element
				show ();
				break;
			case 'd':						//Duplicate the top element
				duplicate ();
				break;
			case 's':						//Swap the top two elements
				swap ();
				break;
			case 'c':						//Clear the stack
				clear ();
				break;
			case '\n':						//Print output of the line
				printf ("%.8g\n", pop ());
				break;
			default:				
				if (type >= 'A' && type <= 'Z')			//Usage of variables
					push (variables [type - 'A']);
				else						//Unknwon command
					printf("Error: unknown command %s\n", input_str);
				break;
		}
		variable = type;						//Stores previous character
	}
	return 0;
}
