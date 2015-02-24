/*
 * Program: dec2hex.c 
 * Purpose: Convert a positive decimal integer to hexadecimal
 * Author:  Kevin Liu
 * Date:    9/5/2014
 */

#include <stdio.h>

/*
 * Function: decToHex()
 * Purpose:  Convert a decimal int to hexadecimal and print it out
 *
 * Parameters:
 *    n: a positive integer
 *
 * Returns: n in hexadecimal
 */
void decToHex(n) {
	if(n < 10)
		printf("%d", n);
	else if(n >= 10 && n < 16)
		printf("%c", n - 10 + 65);
	else {
		decToHex(n / 16);
		if(n % 16 < 10)
			printf("%d", n % 16);
		else
			printf("%c", n%16 - 10 + 65);
	}
}

int main(void) {
	int n;
	scanf("%d", &n);
	printf("0x");
	decToHex(n);
	printf("\n");
}
