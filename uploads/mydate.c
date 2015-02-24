/*
 * mydate.c
 *
 */
#include <stdio.h>

int main(void)
{
	int mon1, day1, dow1, mon2, day2, dow2; 
	int forward = 1; // assume going forward
	int m;
	int days = 0;

	scanf("%d %d %d %d %d", &mon1, &day1, &dow1, &mon2, &day2);
	if (mon1 > mon2 || (mon1 == mon2 && day1 > day2)) // going backward
		forward = 0; 

	if (forward) { // forward
		for (m = mon1; m < mon2; m++) {
			if (m == 2) 
				days += 28; 
			else if (m == 4 || m == 6 || m == 9 || m == 11) 
				days += 30; 
			else 
				days += 31; 
		}
		days = days + day2 - day1;
		dow2 = (dow1 + (days % 7)) % 7; // adjust the day of the week
	}
	else { // backward
		for (m = mon1 - 1; m >= mon2; m--) {
			if (m == 2) 
				days += 28; 
			else if (m == 4 || m == 6 || m == 9 || m == 11) 
				days += 30; 
			else 
				days += 31; 
		}
		days = days + day1 - day2;
		dow2 = (dow1 + 7 - (days % 7)) % 7; // adjust the day of the week
	}

	printf("%d\n", dow2);

	return 0;
}
