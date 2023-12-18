#include <stdio.h>

//Replicate lower () function to using conditional operator


int main ()
{
	char input;
	scanf ("%c", &input);
	
	printf ("Lowercase character: %c\n", (input >= 'A' && input <= 'Z') ? input - 'A' + 'a': input);  //-A+a uses ascii to convert to lowercase
	return 0;
}
