#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//dcl to handle function arguements
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

//Compare function for bsearch
int search (char *ptr, char *types [])
{
	int i = 0;
	while (i < 3 && !strcmp (ptr, types [i++]));
	
	return (i <= 3);
}

//Check if token is a type specifier
int typespec ()
{
	
	static char *types [] = {"char", "int", "void"};
	char *ptr = token;
	
	if (!search (ptr, types))
	{
		printf ("^");
		return NO;
	}
	else
		return YES;
}

//Check if token type qualifier
int typequal ()
{
	static char *typeQ [] = {"const", "volatile", "auto"};
	char *ptr = token;
	
	if (!search (ptr, typeQ))
		return NO;
	else
		return YES;
}

//Declaration specification
void dclspec ()
{
	void dcl ();
	
	char temp [100];
	temp [0] = '\0';
	gettoken ();
	
	do 
	{
		if (tokenType != NAME)
		{
			prevToken = YES;
			dcl ();
		}
		else if (typespec () == YES)
		{
			strcat (temp, " ");
			strcat (temp, token);
			gettoken ();
		}
		else if (typequal () == YES)
		{
			strcat (temp, " ");
			strcat (temp, token);
			gettoken ();
		}
		else
			error_msg ("Unkonwn type in parameter list\n");
	} while (tokenType != ',' && tokenType != ')');
	
	strcat (output, temp);
	if (tokenType == ',')
		strcat (output, ",");
}

//Parse a parameter declarator
void parmdcl ()
{
	do 
	{
		dclspec ();
	} while (tokenType == ',');
	
	if (tokenType != ')')
		error_msg ("Missing ) in parameter declaration\n");
}

//dirdcl productions
void dirdcl ()
{
	int type;
	void dcl ();
	
	if (tokenType == '(')
	{
		dcl ();
		if (tokenType != ')')
			error_msg ("Missing ')'\n");
	}
	//dirdcl -> name
	else if (tokenType == NAME)
		if (name [0] == '\0')
			strcpy (name, token);
	else
		prevToken = YES;
		
	// dirdcl -> (dcl) 

	while ((type = gettoken ()) == PARENTHESIS || type == BRACKETS || type == '(')
		if (type == PARENTHESIS)
			strcat (output, " function returning");
		else if (type == '(')
		{
			strcat (output, " function expecting");
			parmdcl ();
			strcat (output, " and returning");
		}
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
	int no_of_stars = 0;
	
	while (gettoken () == '*')
		no_of_stars++;
		
	dirdcl ();
	
	while (no_of_stars--)
		strcat (output, " pointer to");
}

int main ()
{
	while(gettoken() != EOF)        
    {
        strcpy(datatype, token);
        output[0] = '\0';
        dcl();
        if(tokenType != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, output, datatype);
    }
	return 0;
}
















