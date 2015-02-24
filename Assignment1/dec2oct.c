/*
 * Program: dec2oct.c 
 * Purpose: Convert a positive decimal integer to octal
 * Author:  Kevin Liu
 * Date:    9/5/2014
 */

#include <stdio.h>

/*
 * Function: decToOct()
 * Purpose:  Convert a decimal int to octal and print it out
 *
 * Parameters:
 *    n: a positive integer
 *
 * Returns: no return value 
 */
void decToOct(n) {
	if(n < 8)
		printf("%d", n);
	else {
		decToOct(n / 8);
		printf("%d", n % 8);
	}
}

int main(void) {
	int n;
	scanf("%d", &n);
	printf("0");
	decToOct(n);
	printf("\n");
}
