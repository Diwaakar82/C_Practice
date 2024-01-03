#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'


//Modify the given calculator program to using scanf
int stack_ptr = 0;
int buffer_ptr = 0;

double values [100];
char buffer [100];

//Add character to the buffer
void ungetch (int c) {
    if (buffer_ptr >= 100)
        printf("ungetch: too many characters\n");
    else
        buffer [buffer_ptr++] = c;
}

//Read character from buffer
int getch (void) 
{ 
	return (buffer_ptr > 0) ? buffer [--buffer_ptr] : getchar (); 
}

//Get the next operator
int getop (char input_str [])
{
	int i;
	char c;
	float temp;
	
	while (scanf ("%c", &c) != EOF)
		if ((input_str [0] = c) != ' ' || c != '\t')
			break;
			
	input_str [1] = '\0';
	if (c == EOF)
		return EOF;
	//Return if found an operator
	else if (!isdigit (c) && c != '.' && c != '-')
		return c;
	
	ungetc (c, stdin);
	
	//Read number from input
	scanf ("%f", &temp);
	
	//Write number to string
	sscanf (input_str, "%f", &temp);
	
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
			case ' ':
				break;
			default:
				printf("error: unknown command %s\n", input_str);
				break;
		}
	}
	return 0;
}