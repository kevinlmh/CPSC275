/* CPSC-275 Lab2 Exercise 3
 * Nicholas Wray & Kevin Liu
 * Sep 15 2014
 */

#include <stdio.h>

int main( )
{
   char c = 'Z';
   char *cp = &c;

   printf("cp is 0x%08x\n", cp);
   printf("The character at cp is %c\n", *cp);

   /* Pointer arithmetic - see what cp+1 is */
   cp = cp+1;
   printf("cp is 0x%08x\n", cp);

   /* Note: Do not print *cp, because it points to
      memory not allocated to your program */

   /* Pointer arithmetic on int */
   int i = 1;
   int *ip = &i;
   printf("\nip is %p\n", ip);
   printf("The value at ip is %d\n", *ip);
   ip++;
   printf("ip+1 is %p\n", ip);

   /* Pointer arithmetic on double */
   double d = 2.0;
   double *dp = &d;
   printf("\ndp is %p\n", dp);
   printf("The value at dp is %.1f\n", *dp);
   dp++;
   printf("dp+1 is %p\n", dp);

   /* Pointer arithmetic - see what cp+2 is */
   cp = &c;
   printf("\ncp is 0x%08x\n", cp);
   printf("The character at cp is %c\n", *cp);
   cp = cp+2;
   printf("cp+2 is 0x%08x\n", cp);

   /* Pointer arithmetic on int */
   ip = &i;
   printf("\nip is %p\n", ip);
   printf("The value at ip is %d\n", *ip);
   ip+=2;
   printf("ip+2 is %p\n", ip);

   /* Pointer arithmetic on double */
   dp = &d;
   printf("\ndp is %p\n", dp);
   printf("The value at dp is %.1f\n", *dp);
   dp+=2;
   printf("dp+2 is %p\n", dp);

   return 0;
}