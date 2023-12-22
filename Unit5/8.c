#include <stdio.h>

//Add error handling to the given day_to_year and month_day functions

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year (int year, int month, int day)
{
	int i, isleap;

	isleap = !(year % 4) && (year % 100) || !(year % 400);
	
	//Checking invalid day, month and year
	if (year < 1 || month < 1 || day < 1 || day > daytab [isleap][month])
		return -1;

	for (i = 1; i < month; i++)
		day += daytab[isleap][i];
	return day;
}

void month_day (int year, int yearday, int *month, int *day)
{
	int i, isleap;
	isleap = !(year % 4) && (year % 100) || !(year % 400);
	
	//Checking invalid day and year
	if (year < 1 || yearday < 1 || (isleap && yearday > 366) || (!isleap && yearday > 365))
	{
		*month = -1;
		*day = -1;
		return;
	}

	for (i = 1; yearday > daytab [isleap][i]; i++)
		yearday -= daytab [isleap][i];
	*month = i;
	*day = yearday;
}

int main ()
{
	int yearday, month, day;

	//Valid date
	yearday = day_of_year (1988, 2, 29);
	(yearday != -1) ? printf ("Corresponding year day: %d\n", yearday) : printf ("Invalid date\n");
	
	//Invalid date
	yearday = day_of_year (2020, 2, 31);
        (yearday != -1) ? printf ("Corresponding year day: %d\n", yearday) : printf ("Invalid date\n");

	//Valid date
	month_day (1988, 60, &month, &day);
	(month != -1) ? printf ("Month: %d\nDay: %d\n", month, day) : printf ("Invalid date\n");

	//Invalid date
        month_day (2020, 370, &month, &day);
        (month != -1) ? printf ("Month: %d\nDay: %d\n", month, day) : printf ("Invalid date\n");

	return 0;
}
