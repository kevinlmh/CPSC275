/* 
 * upc.c - computes a UPC Check Digit
 *
 * Author: Peter Yoon
 *
 * Date: September 9, 2013
 *
 */

#include <stdio.h>

int main(void)
{
   int digit01, digit02, digit03, digit04, digit05, digit06;
   int digit07, digit08, digit09, digit10, digit11;
   int sum1, sum2, checkDigit;

   // prompt the user for the first digit and read it
   printf("Enter the first digit: ");
   scanf("%d", &digit01);

   // prompt the user for the first group of five digits and read them
   printf("Enter the first group of five digits: ");
   scanf("%1d%1d%1d%1d%1d", &digit02, &digit03, &digit04, &digit05, &digit06);

   // prompt the user for the second group of five digits and read them
   printf("Enter the first group of five digits: ");
   scanf("%1d%1d%1d%1d%1d", &digit07, &digit08, &digit09, &digit10, &digit11);

   // compute the check digit
   sum1 = digit01 + digit03 + digit05 + digit07 + digit09 + digit11;
   sum2 = digit02 + digit04 + digit06 + digit08 + digit10;
   sum2 += (sum1 * 3);
   sum2 -= 1;
   checkDigit = 9 - (sum2 % 10);

   // print the result
   printf("Check digit: %d\n", checkDigit);

   return 0;
}

