#include <stdio.h>

void squeeze (char s1 [], char s2 [], int n, int m)
{
	int cnt [128] = {0};
	int i = 0;

	while (i < n)
		cnt [s1 [i++]] = 1;
	
	i = 0;
	while (i < m)
		cnt [s2 [i++]] = 0;

	i = 0;

	while (i < n)
	{
		if (cnt [s1 [i]])
			printf ("%c", s1 [i]);
		i++;
	}
}

int getlin (char s [])
{
	int i = 0;
	char c;

	while ((c = getchar ()) != EOF && c != '\n')
		s [i++] = c;

	return i;
}

int main ()
{
	char s1 [1000], s2 [1000];
	int n = getlin (s1);
	int m = getlin (s2);

	squeeze (s1, s2, n, m);
	printf ("\n");
	return 0;
}
