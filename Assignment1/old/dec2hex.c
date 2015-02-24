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
void decToHex(int n) {
	char hex[100];
	int i = -1;
	do {
		hex[++i] = n%16 > 9? n%16-10+65 : n%16 + 48;
		n /= 16;
	} while (n > 0);
	printf("0x");
	for(i; i >= 0; i--)
		printf("%c",hex[i]);
	printf("\n");
} //decToHex()

int main() {
	int dec;
	scanf("%d", &dec);
	decToHex(dec);
	return 0;
}
