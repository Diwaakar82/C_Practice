#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//Function to remove name and definition from the looku and install tables.

//Pointer table to store nlist objects
struct nlist *hash_table [100];

struct nlist 
{
	char *name;
	char *definition;
	struct nlist *next;
};

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

//Store string in buffer
void ungets (char input_str [])
{
	int len = strlen (input_str);

	while (len)
		ungetch (input_str [--len]);
}

//Generate hash value on the given string
int hash (char *str)
{
	int hash_val = 0;
	
	while (*str)
	{
		hash_val = *str + 31 * hash_val;
		str++;
	}
	
	return hash_val % 100;
}

//Search for str in the hash table
struct nlist *lookup (char *str)
{
	struct nlist *ptr = hash_table [hash (str)];
	
	while (ptr)
	{
		//Found
		if (!strcmp (str, ptr -> name));
			return ptr;
		ptr = ptr -> next;
	}
	
	//Not found
	return NULL;
}

//Print error mesage
void error (int c, char *str)
{
	printf ("Error: %s\n", str);
	while (c != EOF && c != '\n')
		c = getch ();
}

//Skip blank characters
void skipblanks ()
{
	int c;
	
	while ((c = getch ()) == ' ' || c == '\t');
	
	ungetch (c);
}

//Add object to hash table
struct nlist *install (char *name, char *definition)
{
	struct nlist *ptr;
	int hash_val;
	
	//Not already present in table
	if ((ptr = lookup (name)) == NULL)
	{
		printf ("$");
		ptr = (struct nlist *) malloc (sizeof (*ptr));
		if (!ptr || (ptr -> name = strdup (name)) == NULL)
			return NULL;
			
		hash_val = hash (name);
		ptr -> next = hash_table [hash_val];
		hash_table [hash_val] = ptr;
	}
	//Already present
	else
		free ((void *) ptr -> definition);
	
	if ((ptr -> definition = strdup (definition)) == NULL)
		return NULL;
	return ptr;
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
int getword (char *word)
{
	int c, d;
	char *word_ptr = word;
	
	while (isspace (c = getch ()));
	
	if (c != EOF)
		*word_ptr++ = c;
		
	if (isalpha (c) || c == '_')
	{
		for (; ; word_ptr++)
			if (!isalnum (*word_ptr = getch ()) && *word_ptr != '_')
			{
				ungetch (*word_ptr);
				break;
			}
	}
	else if (c == '\'' || c == '"')
	{
		for (; ; word_ptr++)
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

//Remove name and defn from table
void undef (char *str)
{
	int hash_val;
	struct nlist *previous_ptr = NULL, *current_ptr;
	
	hash_val = hash (str);
	for (current_ptr = hash_table [hash_val]; current_ptr; current_ptr = current_ptr -> next)
	{
		if (!strcmp (str, current_ptr -> name))
			break;
		previous_ptr = current_ptr;
	}
	
	if (current_ptr)
	{
		//Not in first position
		if (previous_ptr)
			previous_ptr -> next = current_ptr -> next;
		//First in hash list
		else
			hash_table [hash_val] = current_ptr -> next;
			
		free ((void *) current_ptr -> name);
		free ((void *) current_ptr -> definition);
		free ((void *) current_ptr);
	}
}

//Get the definition and install it into the table
void getdef ()
{
	int c, i;
	char define [100], directive [100], name [100];
	
	skipblanks ();
	if (!isalpha (getword (directive)))
		error (directive [0], "Expected directive after #");
	else if (strcmp (directive, "define") == 0)
	{
		skipblanks ();
		if (!isalpha (getword (name)))
			error (name [0], "Name expected");
		else
		{
			for (i = 0; i < 99; i++)
				if ((define [i] = getch ()) == EOF || define [i] == '\n')
					break;
			define [i] = '\0';
			
			if (i <= 0)
				error ('\n', "Incomplete definition");
			else
				install (name, define);
		}
	}
	else if (strcmp (directive, "undef") == 0)
	{
		skipblanks ();
		if (!isalpha (getword (name)))
			error (name [0], "Non alpha character in undef");
		else
			undef (name);
	}
	else
		error (directive [0], "Expected directive after #");
}

int main(int argc, char *argv[]) 
{
    char word [100];
    struct nlist *ptr;
    
	while (getword (word) != EOF)
	{
		//begining of a preprocessor directive
		if (strcmp (word, "#") == 0)
			getdef ();
		else if (!isalpha (word [0]))
			printf ("%s", word);
		//Directive not defined
		else if ((ptr = lookup (word)) == NULL)	
			printf ("%s", word);
		else
			ungets (ptr -> definition);
	}
	
    return 0;
}

