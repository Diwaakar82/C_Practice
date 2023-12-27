#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//Update given qsort function to handle -r tag which prints given input in reverse
char *lines [1000];

static char alloc_buffer [1000];
static char *alloc_ptr = alloc_buffer;

//Maintain tag values
static char option = 0;

//Allocate space
char *alloc (int n) 
{
    if (alloc_buffer + 1000 - alloc_ptr >= n) 
	{
        alloc_ptr += n;
        return alloc_ptr - n;
    } 
	else
        return 0;
}

void afree(char *ptr)    /* free storage pointed to by p */
{
    if (ptr >= alloc_buffer && ptr < alloc_buffer + 1000)
        alloc_ptr = ptr;
}

//Read input lines
int getlin (char input_str []) 
{
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        input_str [i] = c;

    if (c == '\n') 
	{
        input_str [i] = c;
        ++i;
    }

    input_str [i] = '\0';
    return i;
}

//Store read lines in the buffer of line pointers
int readlines(char *lineptr[])
{
	int len, nlines;
	char *p, line [1000];
	nlines = 0;
	while ((len = getlin(line)) > 0)
	if ((p = alloc (len)) == NULL)
		return -1;
	else 
	{
		line [len-1] = '\0';
		strcpy (p, line);
		lineptr [nlines++] = p;
	}
	return nlines;
}

//Print the output
void writelines (char *lineptr [], int nlines)
{
	if (option & 2)
		for (int i = nlines - 1; i >= 0; i--)
			printf ("%s\n", lineptr [i]);
	else
		for (int i = 0; i < nlines; i++)
			printf ("%s\n", lineptr [i]);
}

//Swap function
void my_swap(void *v[], int i, int j)
{
	void *temp;
	temp = v [i];
	v [i] = v[j];
	v[j] = temp;
}

//Modified sort function
void q_sort (void *lineptr[], int left, int right, int (*comp) (void *, void *))
{
	int i, last;

	if (left >= right)
		return;

	my_swap (lineptr, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
			if ((*comp)(lineptr [i], lineptr [left]) < 0)
				my_swap (lineptr, ++last, i);
	
	my_swap (lineptr, left, last);
	q_sort (lineptr, left, last - 1, comp);
	q_sort (lineptr, last + 1, right, comp);
}

//Compare the numbers by converting to number
int numcmp(char *s1, char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

//Compare character by character ignoring case
int charcmp (char *s1, char *s2)
{
	for (; tolower (*s1) == tolower (*s2); s1++, s2++)
		if (*s1 == '\0')
			return 0;
	return tolower (*s1) - tolower (*s2);
}

int main (int argc, char *argv[])
{
	int nlines, c, rc = 0;
	int numeric = 0;
	char *lineptr [1000];

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		while (c = (*++argv[0]))
		{
			switch (c)
			{
				case 'n':
					option |= 1;
					break;
				case 'r':
					option |= 2;
					break;
				case 'f':
					option |= 4;
					break;
				default:
					printf ("Illegal option\n");
					argc = 1;
					rc = -1;
			}
		}
	}

	if (argc)
		printf ("sort -nr\n");
	else if ((nlines = readlines (lineptr)) >= 0) 
	{
		if (option & 1)
            q_sort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
		else if (option & 4)
			q_sort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
        else
           	q_sort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) strcmp);
	} 
	else 
	{
		printf("input too big to sort\n");
		return -1;
	}

	writelines	(lineptr, nlines);
	return 0;
}
