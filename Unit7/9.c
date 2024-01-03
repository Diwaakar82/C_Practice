#include <stdio.h>

//Write a version of isupper which efficiently uses time and space

//Macro saves time but uses more space as each use gets replaced by the whole macro
#define isUpper(ch) ((ch >= 'A') && (ch <= 'Z')) ? 1 : 0

//Saves space but more time due to function calls
int isupper (char ch)
{
	if ((ch >= 'A') && (ch <= 'Z'))
		return 1;
	else
		return 0;
}

int main ()
{
	printf ("Usage of isupper as function: %d\n", isupper ('R'));
	printf ("Usage of isupper as macro: %d\n", isUpper ('R'));
	return 0;
}
