#include <stdio.h>

float celsiustofahrenheit (float celsius)
{
	return (9.0 / 5.0) * celsius + 32.0;
}
int main ()
{
	float fahr, celsius;
	int lower, upper, step;
	lower = 0;
	upper = 100;
	step = 10;
	fahr = lower;
	printf ("Celsius   Fahrenheit\n");
	while (celsius <= upper) 
	{
		fahr = celsiustofahrenheit (celsius);
		printf("%6.0f \t     %3.2f\n", celsius, fahr);
		celsius += step;
	}

	return 0;
}
