#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//Update given qsort function to handle -d which considers only numbers, letters and blanks for comparison
char *lines [1000];

static char alloc_buffer [1000];
static char *alloc_ptr = alloc_buffer;

//Maintain tag values
static char option = 0;
int position1 = 0, position2 = 0;

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

//Store a substring of str1 in str2 starting from pos1 till pos2
void substr (char *str1, char *str2)
{
	int i, j, length;

	length = strlen (str1);
	if (position2 > 0 && length > position2)
		length = position2;
	else if (position2 > 0 && length < position2)
		printf ("String too short\n");
	
	for (j = 0, i = position1; i < length; i++, j++)
		str2 [j] = str1 [i];

	str2 [j] = '\0';
}

//Compare the numbers by converting to number
int numcmp(char *str1, char *str2)
{
	double v1, v2;
	char field [100];
	
	substr (str1, field);
	v1 = atof (field);
	substr (str2, field);
	v2 = atof (field);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

//Compare character by character ignoring case and based on -d flag
int charcmp (char *s1, char *s2)
{
	char ch1, ch2;
	int i, j, endposition;
	int isFold = (option & 4) ? 1 : 0;
	int isDir = (option & 8) ? 1 : 0;
	
	i = j = position1;
	if (position2 > 0)
		endposition = position2;
	else if ((endposition = strlen (s1)) > strlen (s2))
		endposition = strlen (s2);

	do 
	{
		if (isDir)
		{
			while (!isalnum (*s1) && *s1 != ' ' && *s1 != '\0')
				s1++;
			while (!isalnum (*s2) && *s2 != ' ' && *s2 != '\0')
				s2++;
		}
		
		if (i < endposition && j < endposition)
		{
			ch1 = isFold ? tolower (*s1) : *s1;
			s1++;
			ch2 = isFold ? tolower (*s2) : *s2;
			s2++;
		
			if (ch1 == ch2 && ch1 == '\0')
				return 0; 
		}
	}while (ch1 == ch2 && ch1 != '\0');
	
	for (; tolower (*s1) == tolower (*s2); s1++, s2++)

	return ch1 - ch2;
}

//Read the command line arguements and set the flags
void readargs (int argc, char *argv [])
{
	int c;
	
	while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+')
	{
		if (c == '-' && !isdigit (*(argv [0] + 1)))
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
					case 'd':
						option != 8;
						break;
					default:
						printf ("Illegal option\n");
				}
			}
		else if (c == '-')
			position2 = atoi (argv [0] + 1);
		else if ((position1 = atoi (argv [0] + 1)) < 0)
			printf ("Wrong usage of sort: sort -dfnr [+pos1] [-pos2]\n");
	}
	
	if (argc || position1 > position2)
		printf ("Wrong usage of sort: sort -dfnr [+pos1] [-pos2]\n");
}

int main (int argc, char *argv[])
{
	int nlines, rc = 0;
	int numeric = 0;
	char *lineptr [1000];
	
	readargs (argc, argv);

	if ((nlines = readlines (lineptr)) > 0) 
	{
		if (option & 1)
            q_sort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
		else
			q_sort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
	} 
	else 
	{
		printf("input too big to sort\n");
		return -1;
	}

	writelines	(lineptr, nlines);
	return 0;
}
