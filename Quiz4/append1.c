/*
 * Program: append1.c
 * Purpose: Given two strings, combine them into a new string.
 *          rewritten based on append.c from course webiste
 *          all access of arrays are now done by pointers
 * Author: Kevin Liu
 * Date: 09/29/2014
 */ 

#include <stdio.h>

/* functions defined in the program */
int nChar(char *);
void append(char *, char *, char *);

int main(void) 
{
   char first[20];
   char second[20];
   char third[40];

   scanf("%s", first);
   scanf("%s", second);

   append(first, second, third);
   printf("%s\n", third);

   return 0;
}

/*
 * Returns the number of characters of the string s.
 */
int nChar(char *s)
{
   int i = 0;

   /* look for the end of string */
   while (*(s+i))
      i++;

   return i;
}

/*
 *  Returns the result of appending the characters in s1 and s2 to s3.
 *  Note: Two strings are separated by a space in s3.
*/
void append(char *s1, char *s2, char *s3) 
{
   int k, count = 0;

   /* copy the first word */
   for (k = 0; k < nChar(s1); k++) {
      *(s3 + count) = *(s1 + k);
      count++;
   }

   /* insert a space */
   *(s3 + count) = ' ';
   count++;

   /* copy the second word */
   for (k = 0; k < nChar(s2) + 1; k++) {
      *(s3+count) = *(s2 + k);
      count++;
   }
}
