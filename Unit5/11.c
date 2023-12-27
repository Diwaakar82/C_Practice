#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Modify the detab and entab programs to accept command line arguements

//Get input string
int getlin (char input_str [])
{
	int c, i;
	for (i = 0; (c = getchar ()) != EOF && c != '\n'; ++i)
		input_str [i] = c;
	
	if (c == '\n') 
	{
		input_str [i] = c;
		++i;
	}
	input_str [i] = '\0';

	return i;
}

//Replace spaces with tabs
void entab (char input_str [], int tabs [], int length)
{
	int cnt = 0;
	int i = 0;

	for (int j = 0; j < length; j++)
	{
		if (input_str [j] == ' ')
		{
			int next_char = j + 1;
			while (input_str [next_char] == ' ')
			{
				next_char++;
				while (i < 10 && next_char > tabs [i++]);

				if (next_char == tabs [i])
				{
					int spaces = next_char - j;
					while (spaces--)
						printf (" ");
					j = next_char;
				}
			}
			for (int k = j + 1; k <= next_char; k++)
				printf (" ");
			j = next_char - 1;
		}
		else
		{
			printf ("%c", input_str [j]);
			cnt++;
		}
	}
}

//
void detab (char input_str [], int tabs [], int length)
{
	int i = 0, ntab, cnt = 0;
	
	while (i < length)
	{
		if (input_str [i] == '\t')
		{
			ntab = tabs [1] - cnt + 1;
			for (int j = 0; j < ntab; j++)
				printf (" ");
			cnt = 0;
		}
		else if (input_str [i] == '\n')
		{
			cnt = 0;
			printf ("\n");
		}
		else
			printf ("%c", input_str [i]);
		cnt++;
		if (cnt == tabs [1])
			cnt = 0;
		i++;
	}
}

//String to number
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

//Retrieve the predefined tab stops given by user and store in an array
void set_tab_stops (int argc, char *argv [], int tabs [])
{
	int i = 0;
	while (argc--)
		tabs [i++] = atoi (*(++argv));
}

int main (int argc, char *argv [])
{
	int tabs [1000], i = 0, length;
	tabs [0] = -1;

	set_tab_stops (argc - 1, argv, tabs);
	
	if (tabs [0] == -1)
		while (tabs [i - 1] < 40)
			tabs [i] = tabs [i - 1] + 4;

	char input_str [1000];
	length = getlin (input_str);

	entab (input_str, tabs, length);
	return 0;
}
