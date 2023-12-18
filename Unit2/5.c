#include <stdio.h>

int any (char s1 [], char s2 [], int n, int m)
{
	int cnt [128] = {0};
	int i = 0;

	while (i < m)
		cnt [s2 [i++]] = 1;

	i = 0;
	while (i < n)
		if (cnt [s1 [i]])
			return i;
		else
			i++;

	return -1;
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

	printf ("First common character: %d\n", any (s1, s2, n, m));
	return 0;
}
