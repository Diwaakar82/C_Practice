#include <stdio.h>
#include <ctype.h>

int htoi (char s [], int len)
{
	int n = 0, i = 0;
	if (s [i] == '0')
		i += 2;

	while (i < len)
	{
		if (s [i] >= '0' && s [i] <= '9')
			n = 16 * n + s [i] - '0';
		else
			n = 16 * n + tolower (s [i]) - 'a' + 10;
		i++;
	}
	return n;
}
int main ()
{
	char s [1000], c;
	int i = 0;

	while ((c = getchar ()) != EOF && c != '\n')
		s [i++] = c;
	
	printf ("\nInteger value of %s: %d\n", s, htoi (s, i));
	return 0;
}
