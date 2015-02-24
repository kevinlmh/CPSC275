/* 
 * addfrac1.c - adds two fractions entered at the same time.
 *
 * Author: Peter Yoon
 *
 * Date: September 16, 2013
 *
 */

#include <stdio.h>

int main(void)
{
   int num1, num2, denom1, denom2; // numerators and denominators of 
                                   // the two fractions

   // prompt the user for a number
   printf("Enter two fractions separated by a plus sign: ");

   // read input
   scanf("%d/%d+%d/%d", &num1, &denom1, &num2, &denom2);

   // print the result
   printf("The sum is %d/%d.\n", num1*denom2+num2*denom1, denom1*denom2);

   return 0;
}

