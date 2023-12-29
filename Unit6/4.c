#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//Group variable names based on first num characters

struct tree_node
{
	char *word;
	int count;
	struct tree_node *left, *right;
};

struct tree_node *list [100];
int treenode_ptr = 0;

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
        printf ("ungetch: Printingy too many characters\n");
    else
        buffer [buffer_ptr++] = c;
}

//Make a tree node
struct tree_node *talloc ()
{
	return (struct tree_node *)malloc (sizeof (struct tree_node));
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

//Compare words and update the match member of tree_node
int compare (char *str, struct tree_node *ptr)
{
	int i;
	char *t = ptr -> word;
	
	for (i = 0; *str == *t; i++, str++, t++)
		if (*str == '\0')
			return 0;
	
	return *str - *t;
}

//Add node with word at or below ptr
struct tree_node *addtreex (struct tree_node *ptr, char *word)
{
	int condition;
	
	if (!ptr)
	{
		ptr = talloc ();
		ptr -> word = strdup (word);
		ptr -> count = 1;
		ptr -> left = ptr -> right = NULL;
	}
	else if ((condition = compare (word, ptr)) < 0)
		ptr -> left = addtreex (ptr -> left, word);
	else if (condition > 0)
		ptr -> right = addtreex (ptr -> right, word);
	else
		ptr -> count++;
	return ptr;
}

//Sort the list of pointers to tree nodes
void sortlist ()
{
	int gap, i, j;
	struct tree_node *temp;
	
	for (gap = treenode_ptr / 2; gap > 0; gap /= 2)
	{
		for (i = gap; i < treenode_ptr; i++)
		{
			for (j = i - gap; j >= 0; j -= gap)
			{
				if (list [j] -> count >= list [j + gap] -> count)
					break;
				
				temp = list [j];
				list [j] = list [j + gap];
				list [j + gap] = temp;
			}
		}
	}
}
//Store in list pointers to tree nodes
void treestore (struct tree_node *ptr)
{
	if (ptr)
	{
		treestore (ptr -> left);
		if (treenode_ptr < 100)
			list [treenode_ptr++] = ptr;
		treestore (ptr -> right);
	}
}

int main (int argc, char *argv [])
{
	struct tree_node *root;
	char word [100];
	int i;
	
	root = NULL;
	while (getword (word, 100) != EOF)
	{
		if (isalpha (word [0]))
			root = addtreex (root, word);
	}
	
	treestore (root);
	sortlist ();
	
	printf ("Printing tree nodes:\n"); 
	for (i = 0; i < treenode_ptr; i++)
		printf ("%d: %s\n", list [i] -> count, list [i] -> word);
	return 0;
}

