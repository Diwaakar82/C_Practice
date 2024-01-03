#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

//Modify minscanf to handle more facilities of scanf

//Modified minscanf
void minscanf (char *fmt, ...)
{
	va_list arguement_ptr;
	char *ptr, *string_val;
	int *integer_val;
	double *double_val;
	unsigned *unsigned_val;
	
	va_start (arguement_ptr, fmt);
	
	for (ptr = fmt; *ptr; ptr++)
	{
		//Print all character if not %
		if (*ptr != '%')
		{
			putchar (*ptr);
			continue;
		}
		
		switch (*++ptr)
		{
			//Handle integers
			case 'd':
			case 'i':
				integer_val = va_arg (arguement_ptr, int *);
				scanf ("%d", integer_val);
				break;
			//Handle floating point numbers
			case 'f':
				double_val = va_arg (arguement_ptr, double *);
				scanf ("%f", double_val);
				break;
			//Handle strings
			case 's':
				string_val = va_arg (arguement_ptr, char *);
				scanf ("%s", string_val);
				break;
			//Handle unsigned characters
			case 'x':
			case 'X':
			case 'u':
			case 'o':
				unsigned_val = va_arg (arguement_ptr, unsigned *);
				scanf ("%u", unsigned_val);
				break;
			default:
				printf ("Invalid specifier");	
		}
	}
	
	va_end (arguement_ptr);
}

int main ()
{
	int var1;
	float var2;
	char var3 [50];
	unsigned var4;
	
	minscanf ("%d%f%s%u", &var1, &var2, var3, &var4);
	printf ("Variables:\n%d\n%f\n%s\n%u\n", var1, var2, var3, var4);
	return 0;
}
