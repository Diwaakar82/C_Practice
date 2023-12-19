#include <stdio.h>

//Expand shorthand regex expressions like a-z to abcd...z
int main ()
{
	char input_str [1000], modified_str [1000];
	scanf ("%s", input_str);

	int i = 0, j = 0;
	while (input_str [i] != '\0')
	{
		if (i > 0 && input_str [i] == '-')	//If encountered a - check previous and next char.
		{
			char previous_char = input_str [i - 1] + 1, next_char = input_str [i + 1];
			if (next_char >= previous_char)                         //Checking for valid condition like a-z and not z-a
				while (next_char > previous_char)
					modified_str [j++] = previous_char++;
			else
				modified_str [j++] = input_str [i];
		}
		else
			modified_str [j++] = input_str [i];
		i++;
	}
	modified_str [j] = '\0';

	printf ("Modified: %s\n", modified_str);
	return 0;
}
