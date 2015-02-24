/* 
 * sep.c - inserts three blank spaces between digits in a five-digit number.
 *
 * Author: Peter Yoon
 *
 * Date: September 16, 2013
 *
 */

#include <stdio.h>

int main(void)
{
   int number; // five-digit input number

   // prompt the user for a number
   printf("Enter a five-digit number: ");

   // read input
   scanf("%d", &number);

   // get the first digit
   printf("%d  ", number / 10000);
   number %= 10000;

   // get the second digit
   printf("%d  ", number / 1000);
   number %= 1000;

   // get the third digit
   printf("%d  ", number / 100);
   number %= 100;

   // get the fourth digit
   printf("%d  ", number / 10);
   number %= 10;

   // print the last digit
   printf("%d\n", number);

   return 0;
}
