#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
//Modify getline, atoi, itoa, reverse, strindex and getop functions using pointers.

char buffer [1000];
double values [1000];
int buffer_ptr = 0, stack_ptr;

int getch ()
{
	return (buffer_ptr > 0) ? buffer [--buffer_ptr] : getchar ();
}

void ungetch (int c)
{
	if (buffer_ptr >= 1000)
		printf ("Buffer full\n");
	else
		buffer [buffer_ptr++] = c;
}

//Modified getline function
int getlin (char *input_str)
{
	int c;
	char *ptr = input_str;

	while ((c = getch ()) != EOF)
		*ptr++ = c;

	if (c == '\n')
		*ptr++ = c;
	*ptr = '\0';
	
	return ptr - input_str;
}

//Modified reverse function
void reverse (char *input_str)
{
	char *ptr = input_str;

	while (*ptr++);
	*ptr--;
	*ptr--;

	while (input_str < ptr)
	{
		char temp = *input_str;
		*input_str = *ptr;
		*ptr = temp;

		input_str++;
		ptr--;
	}
}

//Modified atoi function
int atoi (char *input_str)
{
	int number = 0, sign;

	while (isspace (*input_str++));
	*input_str--;

	sign = (*input_str == '-') ? -1 : 1;

	if (*input_str == '+' || *input_str == '-')
		*input_str++;

	while (isdigit (*input_str))
		number = number * 10 + (*input_str++ - '0');

	return number * sign; 
}

//Modified itoa function
void itoa (int number, char *str_number)
{
	int sign;
	char *ptr = str_number;

	if ((sign = number) < 0)
		number = -number;

	do
	{
		*str_number++ = number % 10 + '0';
	}while ((number /= 10) > 0);

	if (sign < 0)
		*str_number++ = '-';
	*str_number = '\0';
	reverse (ptr);
}

//Modified strindex function
int strindex (char *string1, char *string2)
{
	char *ptr1 = string1;
	char *ptr2, *ptr3;
	
	while (*string1++)
	{
		for (ptr2 = string1, ptr3 = string2; *ptr3 && *ptr2 == *ptr3; ptr2++, ptr3++);

		if (ptr3 > string2 && *ptr3 == '\0')
			return string1 - ptr1;
	}
	return -1;
}

//Modified version of getop function
int getop (char *input_str)
{
	int c;

	while ((*input_str = c = getch ()) == ' ' || c == '\t');
	*(input_str + 1) = '\0';

	if (!isdigit (c) && c != '.')
		return c;
	if (isdigit (c))
		while (isdigit (*++input_str = c = getch ()));
	if (c == '.')
		while (isdigit (*++input_str = c = getch ()));

	*input_str = '\0'; 
	
	if (c != EOF)
		ungetch (c);
	return NUMBER;
}

//Insert read number to the stack
void push (double number)
{
	if (stack_ptr < 1000)
		values [stack_ptr++] = number;
	else
		printf ("Stack full\n");
}

//Remove number at the top of stack
double pop ()
{
	if (stack_ptr > 0)
		return values [--stack_ptr];
	else
		printf ("Stack empty\n");
}

int main ()
{
	int type;
	double operand2;
	char input_str [1000];

	while ((type = getop (input_str)) != EOF)
	{	
		switch (type)
		{
			case NUMBER:
				push (atoi (input_str));
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
			case '\n':
				printf ("%.8g\n", pop ());
				break;
			default:
				printf ("Undefined operation %s\n", input_str);
				break;
		}

	}
	
	//printf ("%d\n", strindex (test, s));
	return 0;
}
