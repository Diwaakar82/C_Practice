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

//Read and return the next word
int getword (char *word, int limit)
{
	int c, t;
	char *ptr = word;
	
	while (isspace (c = getch ()));
	
	//ungetch (c);
	if (isalpha (c) || c == '_' || c == '#')
	{
		*ptr++ = c;
		for (; --limit; ptr++)
		{
			if (!isalnum (*ptr = getch ()) && *ptr != '_')
			{
				ungetch (*ptr);
				break;
			}
		}
		return word [0];
	}
	else if (c == '/')
	{
		if (c = getch () == '/')
			while (getch () == '\n');
		else if (c == '*')
		{	
			c = getch ();
			while (c != '*' && (c = getch ()) != '/');
		}
	}
	else if (c == '\"')
		while (getch () != '\"');
	
	if (c != EOF)
		*ptr++ = c;
	*ptr = '\0';
	
	return word [0];
}

int main ()
{
	char words [100];
	getword (words, 100);
	
	printf ("%s", words);
	return 0;
}
