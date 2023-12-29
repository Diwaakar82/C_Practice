#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//List all words in the document along with line numbers ignoring noise words.

//List to maintain line numbers
struct linked_list
{
	int line_number;
	struct linked_list *next;
};

//Tree node
struct tree_node
{
	char *word;
	struct linked_list *lines;
	struct tree_node *left, *right;
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
	
	//Skip space characters
	while ((c = getch ()) == ' ' || c == '\t');
	
	if (c != EOF)
		*word_ptr++ = c;
	
	//Read words
	if (isalpha (c) || c == '_' || c == '#')
	{
		for (; --limit; word_ptr++)
			if (!isalnum (*word_ptr = getch ()) && *word_ptr != '_')
			{
				ungetch (*word_ptr);
				break;
			}
	}
	//Ignore string literals
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
	//Ignore comments
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

//Print tree in order (inorder traversal)
void treexprint (struct tree_node *ptr)
{
	struct linked_list *temp;
	
	if (ptr)
	{
		treexprint (ptr -> left);
		printf ("%s: ", ptr -> word);
		for (temp = ptr -> lines; temp; temp = temp -> next)
			printf ("%d ", temp -> line_number);
		printf ("\n");
		treexprint (ptr -> right);
	}
}

//Allocate a linked list node
struct linked_list *lalloc ()
{
	return (struct linked_list *) malloc (sizeof (struct linked_list));
}

//Identify noisewords
int noiseword (char *word)
{
	char *noisewords [] = {"a", "an", "and", "are", "in", "is", "of", "or", "that", "the", "this", "to"};
	
	int condition, mid, low = 0;
	int high = sizeof (noisewords) / sizeof (char *) - 1;
	
	//Binary search to find if matches any noise word
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if ((condition = strcmp (word, noisewords [mid])) < 0)
			high = mid - 1;
		else if (condition > 0)
			low = mid + 1;
		else
			return mid;
	}
	
	return -1;
}

//Add line number to the linked list
void add_line (struct tree_node *ptr, int line_number)
{
	struct linked_list *temp;

	temp = ptr -> lines;
	while (temp -> next && temp -> line_number != line_number)
		temp = temp -> next;
		
	if (temp -> line_number != line_number)
	{
		temp -> next = lalloc ();
		temp -> next -> line_number = line_number;
		temp -> next -> next = NULL;
	} 
}

//Add node with word at or below ptr
struct tree_node *addtreex (struct tree_node *ptr, char *word, int line_number)
{
	int condition;
	
	//Create new node
	if (!ptr)
	{
		ptr = talloc ();
		ptr -> word = strdup (word);
		ptr -> lines = lalloc ();
		ptr -> lines -> line_number = line_number;
		ptr -> lines -> next = NULL;
		ptr -> left = ptr -> right = NULL;
	}
	//If word already exists add line number
	else if (!(condition = strcmp (word, ptr -> word)))
		add_line (ptr, line_number);
	//Traverse left subtree
	else if (condition < 0)
		ptr -> left = addtreex (ptr -> left, word, line_number);
	//Traverse right subtree
	else if (condition > 0)
		ptr -> right = addtreex (ptr -> right, word, line_number);
	return ptr;
}

int main (int argc, char *argv [])
{
	struct tree_node *root;
	char word [100];
	
	int line_number = 1;
	
	root = NULL;
	while (getword (word, 100) != EOF)
	{
		if (isalpha (word [0]) && noiseword (word) == -1)
			root = addtreex (root, word, line_number);
		else if (word [0] == '\n')
			line_number++;
	}
	
	printf ("Printing tree nodes:\n");
	treexprint (root);
	return 0;
}

