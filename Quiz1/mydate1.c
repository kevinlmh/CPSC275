/*
 * Program: mydate1.c 
 * Purpose: Determines what day of the week a date is based on a given input
 * Author:  Kevin Liu
 * Date:    9/14/2014
 */
#include <stdio.h>

int main(void)
{
	int num_days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int mon1, day1, dow1, mon2, day2, dow2; 
	int forward = 1; // assume going forward
	int m;
	int days = 0;

	scanf("%d %d %d %d %d", &mon1, &day1, &dow1, &mon2, &day2);
	if (mon1 > mon2 || (mon1 == mon2 && day1 > day2)) // going backward
		forward = 0; 

	if (forward) { // forward
		for (m = mon1; m < mon2; m++) {
			days += num_days_in_month[m - 1];
		}
		days = days + day2 - day1;
		dow2 = (dow1 + (days % 7)) % 7; // adjust the day of the week
	}
	else { // backward
		for (m = mon1 - 1; m >= mon2; m--) {
			days += num_days_in_month[m - 1];
		}
		days = days + day1 - day2;
		dow2 = (dow1 + 7 - (days % 7)) % 7; // adjust the day of the week
	}

	printf("%d\n", dow2);

	return 0;
}
