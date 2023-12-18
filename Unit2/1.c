#include <stdio.h>
#include <limits.h>
#include <float.h>

int main ()
{
	printf ("Using maximum values:\n");
	printf ("\nSigned integer maximum: %d", INT_MAX);
	printf ("\nSigned integer minimum: %d", INT_MIN);
	printf ("\nUnsigned integer maximum: %u", UINT_MAX);

	printf ("\n\nSigned character maximum: %d", SCHAR_MAX);
	printf ("\nSigned character minimum: %d", SCHAR_MIN);
        printf ("\nUnsigned character maximum: %d", UCHAR_MAX);
	
	printf ("\n\nSigned long maximum: %ld", LONG_MAX);
        printf ("\nSigned long minimum: %ld", LONG_MIN);
        printf ("\nUnsigned long maximum: %lu", ULONG_MAX);

	printf ("\n\nSigned short maximum: %d", SHRT_MAX);
        printf ("\nSigned short minimum: %d", SHRT_MIN);
        printf ("\nUnsigned short maximum: %d\n", USHRT_MAX);

	printf ("\n\nSigned float maximum: %e", FLT_MAX);
        printf ("\nSigned float minimum: %e", FLT_MIN);

	printf ("\n\nSigned double maximum: %e", DBL_MAX);
	printf ("\nSigned double minimum: %e", DBL_MIN);


	printf ("\nUsing computation:\n");
        printf ("\nSigned integer maximum: %d", (int) ((unsigned int) ~0 >> 1));
        printf ("\nSigned integer minimum: %d", -(int) ((unsigned int) ~0 >> 1) - 1);
        printf ("\nUnsigned integer maximum: %u", (unsigned int) ~0);

        printf ("\n\nSigned character maximum: %d", (char) ((unsigned char) ~0 >> 1));
        printf ("\nSigned character minimum: %d", -(char) ((unsigned char) ~0 >> 1) - 1);
        printf ("\nUnsigned character maximum: %d", (unsigned char) ~0);

        printf ("\n\nSigned long maximum: %ld", (long) ((unsigned long) ~0 >> 1));
        printf ("\nSigned long minimum: %ld", -(long) ((unsigned long) ~0 >> 1) - 1);
        printf ("\nUnsigned long maximum: %lu", (unsigned long) ~0);

        printf ("\n\nSigned short maximum: %d", (short) ((unsigned short) ~0 >> 1));
        printf ("\nSigned short minimum: %d", (short) ((unsigned short) ~0 >> 1) - 1);
        printf ("\nUnsigned short maximum: %d\n", (unsigned short) ~0);


	return 0;
}
