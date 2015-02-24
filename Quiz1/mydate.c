/*
 * Program: mydate.c 
 * Purpose: Determines what day of the week a date is based on a given input
 * Author:  Kevin Liu
 * Date:    9/8/2014
 */
#include <stdio.h>

/*
 * Function: mydate()
 * Purpose:  Given what day of the week a date falls on, determines what day of the week another date from that year will fall ion
 *
 * Parameters:
 *    month: the month of the given date
 *		date: the date of the given date
 *		day: what day of the week the given date is
 *		month2: the month of the second date
 *		date: the second date
 *
 * Returns: what day of the week the second date is
 */
int mydate(int month,int date,int day,int month2,int date2) {
	int num_days_in_month[12] = {31,28,31,30,31,30,30,31,30,31,30,31};
	int diff = 0;
	if(month2 == month) {
			diff = (date2>date)? date2-date : date-date2;
			return (day+(diff%7))%7;
	}	else if(month2 > month) {
		diff += date2;
		month2--;
		while(month2 > month) {
			diff += num_days_in_month[month2-1];
			month2--;
		}
		diff += (num_days_in_month[month-1]-date);
		return (day+(diff%7))%7;
	} else {
		diff += date;
		month--;
		while(month > month2) {
			diff += num_days_in_month[month-1];
			month--;
		}
		diff += (num_days_in_month[month2-1]-date2);
		return (day-(diff%7))%7 > 0 ? (day-(diff%7))%7 : 7+ (day-(diff%7))%7 ;
	}
}

int main(void) {
	int month, date, day, month2, date2;
	scanf("%d %d %d %d %d", &month, &date, &day, &month2, &date2);
	printf("%d\n", mydate(month, date, day, month2, date2));
	return 0;
}

