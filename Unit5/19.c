#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Modified undcl to handle redundant parenthesis
enum { NAME, PARENTHESIS, BRACKETS };
enum { NO, YES };

int tokenType;							//Type of previously read token
char token [100];						//Last token string
char name [100];						//Name of identifier
char output [100];						//Output string
char datatype [100];					//Datatypes like char, int etc
int prevToken = NO;

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

//Print error message
void error_msg (char *msg)
{
	printf ("%s", msg);
	prevToken = YES;
}

//Return next token
int gettoken ()
{
	int c;
	char *ptr = token;
	
	//Return previously read token
	if (prevToken == YES)
	{
		prevToken = NO;
		return tokenType;
	}
	
	//Skip blanks
	while ((c = getch ()) == ' ' || c == '\t');
	
	//Check ()
	if (c == '(')
	{
		//printf ("hkdj");
		if ((c = getch ()) == ')')
		{
			strcpy (token, "()");
			return tokenType = PARENTHESIS;
		}
		else
		{
			ungetch (c);
			return tokenType = '(';
		}
	}
	//Check []
	else if (c == '[')
	{
		for (*ptr++ = c; *ptr != ']';)
		{
			*ptr = getch ();
			if (*ptr != ']')
			{
				if (*ptr == '\n' || *ptr == ')' || *ptr == '(')
				{
					printf ("Missing ]\n");
					ungetch (*ptr);
					*ptr = ']';		
				}
				else
					*ptr++;
			}
		}
		*(++ptr) = '\0';
		
		return tokenType = BRACKETS;
	}
	//Check names
	else if (isalpha (c))
	{
		for (*ptr++ = c; isalnum (c = getch ());)
			*ptr++ = c;
		*ptr = '\0';
		ungetch (c);
		return tokenType = NAME;
	}
	else
		return tokenType = c;
}

//dirdcl productions
void dirdcl ()
{
	//printf ("dirdcl\n");
	int type;
	void dcl ();
	
	// dirdcl -> (dcl) 
	if (tokenType == '(')
	{
		dcl ();
		if (tokenType != ')')
			error_msg ("Missing ')'\n");
	}	
	//dirdcl -> name
	else if (tokenType == NAME)
		strcpy (name, token);
	else
		error_msg ("Expected name or (dcl)\n");
		
	while ((type = gettoken ()) == PARENTHESIS || type == BRACKETS)
		if (type == PARENTHESIS)
			strcat (output, " function returning");
		else
		{
			strcat (output, " array");
			strcat (output, token);
			strcat (output, " of");
		}
}

//dcl productions
void dcl ()
{
	//printf ("dcl\n");
	int no_of_stars = 0;
	
	while (gettoken () == '*')
		no_of_stars++;
		
	dirdcl ();
	
	while (no_of_stars--)
		strcat (output, " pointer to");
}

//Get the next token and push it back
int nexttoken ()
{
	int type;
	type = gettoken ();
	prevToken = YES;
	
	return type;
}

int main ()
{
	int type;
	char temp [100];
	
	while(gettoken() != EOF)        
    {
        strcpy (output, token);
        
        while ((type = gettoken ()) != '\n')
        	if (type == PARENTHESIS || type == BRACKETS)
        		strcat (output, token);
        	else if (type == '*')
        	{
        		if ((type = nexttoken ()) == PARENTHESIS || type == BRACKETS)
        			sprintf (temp, "(*%s)", output);
        		else
        			sprintf (temp, "*%s", output);
        		strcpy (output, temp);
        	}
        	else if (type == NAME)
        	{
        		sprintf (temp, "%s %s", token, output);
        		strcpy (output, temp);
        	}
        	else
        		printf ("Invalid input %s\n", token);
        		
        printf ("%s\n", output);
    }
	return 0;
}
















