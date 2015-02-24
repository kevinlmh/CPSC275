/* 
 * space.c - inserts blank spaces between characters in a string.
 *
 * Author: Peter Yoon
 *
 * Date: October 1, 2013
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *insert_space(char *, int);

int main(void)
{
   char inStr[101];
   int nSpaces;
   char *outStr;

   // read input: number of white spaces and a string of characters
   scanf("%d", &nSpaces);
   scanf("%s", inStr);

   // insert spaces and print the output
   outStr = insert_space(inStr, nSpaces);
   printf("%s\n", outStr);

   // deallocate memory spaced allocated for the new string
   free(outStr);

   return 0;
}

/*
 * insert_space(str, m) function inserts m spaces between characters in the string str.
 *
 */
char *insert_space(char *str, int m)
{
   char *newStr, *q;   // will point to newly allocated string
   int len = strlen(str);
   int i, j, lenNew;

   lenNew = len + (len - 1)*m + 1; // determine the length of new string
   newStr = (char *) malloc(lenNew); // allocate necessary memory

   // process each char except for the last char and the null
   for (q = newStr, i = 0; i < len - 1; i++) {
      *q++ = *str++;  // copy the character at the current position
      for (j = 0; j < m; j++) // insert m spaces
         *q++ = ' ';
   }
   *q++ = *str; // copy the last char of str
   *q = '\0'; // force the null char

   return newStr;
}
