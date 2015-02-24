/* 
 * addfrac.c - adds two fractions
 *
 * Author: Peter Yoon
 *
 * Date: September 9, 2013
 *
 */

#include <stdio.h>

int main(void)
{
   int num1, num2, denom1, denom2; // numerators and denominators of 
                                   // the two fractions to be added

   // prompt the user for the first number and read it
   printf("Enter the first fraction: ");
   scanf("%d/%d", &num1, &denom1);

   // prompt the user for the second number and read it
   printf("Enter the second fraction: ");
   scanf("%d/%d", &num2, &denom2);

   // print the result
   printf("The sum is %d/%d.\n", num1*denom2+num2*denom1, denom1*denom2);

   return 0;
}

