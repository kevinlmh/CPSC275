/* CPSC-275 Lab2 Exercise 2
 * Nicholas Wray & Kevin Liu
 * Sep 15 2014
 */

#include <stdio.h>

void func1(int xval)
{
   int x;
   x = xval;
   /* print the address and value of x here */
   printf("%p\t%d\n", &x, x);
}

void func2(int dummy)
{
   int y;
   /* print the address and value of y here */
   printf("%p\t%d\n", &y, y);
}

int main()
{
   func1(7);
   func2(11);

   return 0;
}