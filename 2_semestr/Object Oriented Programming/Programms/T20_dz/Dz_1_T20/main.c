#include <stdio.h>


int scan_int(char* s) //Input check of year
{
	int a = 0, i = 0;
	while (*s) //while string is not empty
	{
		if ((*s < '0') || (*s > '9') || (i == 4)) //symbol is not number
		{
			return 0;
		}
		a = a * 10 + (*s - '0');
		++s;
		++i;
	}
	return a;
}


void output_weeks(int d_1, int d_2) //Output days of week and their amount
{
	int i;
	for (i = 0; i < 7; i++)
	{
		switch (i)
		{
			case (0):
				if ((i == d_1) || (i == d_2))
					printf("Mon: %d days\n", 53);
				else
					printf("Mon: %d days\n", 52);
				break;
			case (1):
				if ((i == d_1) || (i == d_2))
					printf("Tue: %d days\n", 53);
				else
					printf("Tue: %d days\n", 52);
				break;
			case (2):
				if ((i == d_1) || (i == d_2))
					printf("Wed: %d days\n", 53);
				else
					printf("Wed: %d days\n", 52);
				break;
			case (3):
				if ((i == d_1) || (i == d_2))
					printf("Thu: %d days\n", 53);
				else
					printf("Thu: %d days\n", 52);
				break;
			case (4):
				if ((i == d_1) || (i == d_2))
					printf("Fri: %d days\n", 53);
				else
					printf("Fri: %d days\n", 52);
				break;
			case (5):
				if ((i == d_1) || (i == d_2))
					printf("Sat: %d days\n", 53);
				else
					printf("Sat: %d days\n", 52);
				break;
			default:
				if ((i == d_1) || (i == d_2))
					printf("Sun: %d days\n", 53);
				else
					printf("Sun: %d days\n", 52);

		}
	}
}


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Invalid amount of arguments.\n");
		return (-1);
	}

	int year = scan_int(argv[1]);

	if ((year == 0) || (year <= 2000) || (year > 2100))
	{
		printf("Wrong input format of year.\n");
		return (-1);
	}

	int day_1 = ((year - 2001) + (year - 2001) / 4) % 7; //Search the first day of year

	int day_2 = -1;
	if ((year % 4 == 0) && ((year % 100 != 0) || ((year % 100 == 0) && (year % 400 == 0)))) //Check of leap year
		day_2 = (day_1 + 1) % 7;		
	output_weeks(day_1, day_2);
	return 0;
}