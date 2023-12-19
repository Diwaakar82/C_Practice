#include <stdio.h>
#include <ctype.h>

//Extend the given atof () to work with scientific notations

double atof (char input_number [])
{
	double number, power;
	int i, sign;

	for (i = 0; input_number [i] == ' '; i++);  		//Skips leading spaces
	sign = (input_number [i] == '-');  			//Sets the sign of the number

	while (input_number [i] == '+' || input_number [i] == '-')	//Skips extra +/- symbols
		i++;

	for (number = 0.0; isdigit (input_number [i]); i++)	//Computes values of positive weights
		number = 10.0 * number + (input_number [i] - '0');

	if (input_number [i] == '.')
		i++;

	for (power = 1.0; isdigit (input_number [i]); i++) 
	{
		number = 10.0 * number + (input_number [i] - '0');
		power *= 10.0;
	}
	
	if (sign)
		number = -number;

	number /= power;


	if (input_number [i] == 'e' || input_number [i] == 'E')
	{
		i++;
		int exp_sign = 0, exponent = 0;
		
		if (input_number [i] == '+')
			i++;
		else if (input_number [i] == '-')
		{
			exp_sign++;
			i++;
		}
		
		while (isdigit (input_number [i]))
		{
			exponent *= 10;
			exponent += input_number [i] - '0';
			i++;
		}
		
		if (exp_sign)
			while (exponent--)
				number /= 10;
		else
			while (exponent--)
				number *= 10;
	}

	return number;
}

int main ()
{
	char input_number [1000];
	scanf ("%s", input_number);

	double number = atof (input_number);
	printf ("Modified number: %lf\n", number);
	return 0;
}
