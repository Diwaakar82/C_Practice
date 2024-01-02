#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

//Modify minprintf to handle more facilities of printf

//Modified minprintf
void minprintf (char *fmt, ...)
{
	va_list arguement_ptr;
	char *ptr, *string_val;
	int integer_val;
	double double_val;
	unsigned unsigned_val;
	
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
				integer_val = va_arg (arguement_ptr, int);
				printf ("%d", integer_val);
				break;
			//Handle floating point numbers
			case 'f':
				double_val = va_arg (arguement_ptr, double);
				printf ("%f", double_val);
				break;
			//Handle strings
			case 's':
				string_val = va_arg (arguement_ptr, char *);
				printf ("%s", string_val);
				break;
			//Handle unsigned characters
			case 'x':
			case 'X':
			case 'u':
			case 'o':
				unsigned_val = va_arg (arguement_ptr, unsigned);
				printf ("%u", unsigned_val);
				break;
			default:
				printf ("Invalid specifier");	
		}
	}
	
	va_end (arguement_ptr);
}

int main ()
{
	minprintf ("Interger: %d\nFloating point number: %f\nString: %s\nUnsigned number: %u\n", 1, 2.5, "hbcdj", 78);	
	return 0;
}
