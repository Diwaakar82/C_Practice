#include <stdio.h>
#include <ctype.h>

//Modify the getword function to handle underscores, comments, string constants and preprocessor control lines.

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

//Skip commented characters
int comment ()
{
	int c;
	
	while ((c = getch ()) != EOF)
		if (c == '*')
			if ((c = getch ()) == '/')
				break;
			else
				ungetch (c); 
		else if (c == '/')
		{
			while ((c = getch ()) != '\n');
			break;
		}
		
		return c;
}

//Get next word or character from input
int getword (char *word, int limit)
{
	int c, d;
	char *word_ptr = word;
	
	while (isspace (c = getch ()));
	
	if (c != EOF)
		*word_ptr++ = c;
		
	if (isalpha (c) || c == '_' || c == '#')
	{
		for (; --limit; word_ptr++)
			if (!isalnum (*word_ptr = getch ()) && *word_ptr != '_')
			{
				ungetch (*word_ptr);
				break;
			}
	}
	else if (c == '\'' || c == '"')
	{
		for (; --limit; word_ptr++)
			if ((*word_ptr = getch ()) == '\\')
				*++word_ptr = getch ();
			else if (*word_ptr == c)
			{
				word_ptr++;
				break;
			}
			else if (*word_ptr == EOF)
				break;
	}
	
	else if (c == '/')
	{
		if ((d = getch ()) == '*')
			c = comment ();
		else if (d == '/')
			while ((c = getch ()) != '\n');
		else
			ungetch (d);
	}
	
	*word_ptr = '\0';
	return c;
}

int main ()
{
	char words [100];
	getword (words, 100);
	
	printf ("%s", words);
	return 0;
}
