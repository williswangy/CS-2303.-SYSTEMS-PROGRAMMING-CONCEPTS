/*
======================================================================
Name: YUAN WANG's MONTHLY CALENDAR
Auther: Yuan Wang
Version: 1.00
Description: Dispaly a 12 month calendar for a given year.
======================================================================
*/


#include<stdio.h>


int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31}; //define the days of 12 months

char *months[]= { " ", "\n\nJanuary", "\n\nFebruary","\n\nMarch", "\n\nApril", "\n\nMay", "\n\nJune", 
"\n\nJuly", "\n\nAugust", "\n\nSeptember", "\n\nOctober", "\n\nNovember", "\n\nDecember" };


//function allows users to enter the year
int givenYear(void) 
{
        printf("   *****  MONTHLY CALENDAR  ***** \n\n");
	
        int year;
        printf("Please enter year for this calendar:- ");
	scanf("%d", &year);

	return year;
}

//function that gets the day number of the first day in the given year
int first_day_year(int year)
{
	int first_day, day1, day2, day3;
	
	day1 = (year - 1.)/ 4.0;
	day2 = (year - 1.)/ 100.;
	day3 = (year - 1.)/ 400.;

	first_day = (year + day1 - day2 + day3) % 7;
	return first_day;
}

//function that determine whether the given year is a leap year or not
int isLeapyear(int year)
{
	if((year%4==0 && year%100!=0) || year%400 == 0)
	{
		days_in_month[2] = 29;
		return 1;
	}
	else
	{
		days_in_month[2] = 28;
		return 0;
	}
}

//function that  is used to print 12 months onto the screen
void showCalendar(int year, int first_day)
{
	int month, day;
        
        printf("\n");
	printf(" *** Calendar for %d ***", year);

	// loop through all months
        for ( month = 1; month <= 12; month++ )
	{
		
		printf("%s %d", months[month], year);
		printf("\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
		
		// Determine the position of the first_day
		for ( day = 1; day <= 1 + first_day * 5; day++ )
		{
			printf(" ");
		}
		
		// Print all the dates for one month
		for ( day = 1; day <= days_in_month[month]; day++ )
		{
			printf("%2d", day );
			
			//if the day is before Sat print "  ", otherwise >> start next line Sun.
			if ( ( day + first_day ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
			// Set position for next month
			first_day = ( first_day + days_in_month[month] ) % 7;
	}
}
//main function 
int main(void)
{
	int year, first_day;
	
	year = givenYear();
        
	first_day = first_day_year(year);
	isLeapyear(year);
	showCalendar(year, first_day);
	
	printf("\n");
}
