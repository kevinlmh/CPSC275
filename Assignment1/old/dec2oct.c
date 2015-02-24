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
 * Returns: n in octal
 */
void decToOct(int n) {
	char oct[100];
	int i = -1;
	do {
		oct[++i] = 48 + n%8;
		n /= 8;
	} while (n > 0);
	printf("0");
	for(i; i >= 0; i--)
		printf("%c",oct[i]);
	printf("\n");
} //decToOct()

int main() {
	int dec;
	scanf("%d", &dec);
	decToOct(dec);
	return 0;
}
