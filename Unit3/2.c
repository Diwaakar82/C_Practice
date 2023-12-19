#include <stdio.h>

//Convert escape sequences to visible characters and vice versa.
//

//Function to get input string and return its length
int getlin (char input_str [])
{
	int i = 0;
	char c;

	while ((c = getchar ()) != EOF)
		input_str [i++] = c;

	input_str [i] = '\0';
	return i;
}

//Function to change escape sequences to printable characters.

int escape (char input_str [], int length, char modified_str [])
{
	int i = 0, j = 0;

	while (i < length)
	{
		switch (input_str [i])
		{
			case '\n':
				modified_str [j++] = '\\';
				modified_str [j++] = 'n';
				break;
			case '\t':
				modified_str [j++] = '\\';
				modified_str [j++] = 't';
				break;
			default:
				modified_str [j++] = input_str [i];
		}
		i++;
	}
	modified_str [j] = '\0';
	return j;
}

//Funtion to revert the effects of escape.
int revert (char input_str [], int length)
{
	int i = 0, j = 0;

	while (i < length)
	{
		if (i + 1 < length && input_str [i] == '\\')
		{
			switch (input_str [i + 1])
			{
				case 'n':
					input_str [j] = '\n';
					i++;
					break;
				case 't':
					input_str [j] = '\t';
					i++;
					break;
				default:
					input_str [j] = input_str [i];
			}
		}
		else
			input_str [j] = input_str [i];
		i++;
		j++;
	}
	return j;
	
}

int main ()
{
	char input_str [1000];
	int length1 = getlin (input_str);

	char modified_str [1000];
	int length2 = escape (input_str, length1, modified_str);
	printf ("\nModified string: %s\n", modified_str);

	//char original_str [1000];
	int length3 = revert (modified_str, length2);
	printf ("\nModified string: %s\n", modified_str);
	return 0;
}
