/*
    This program reads two strings, s1 and s2, from stdin and appends the 
    characters in s2 to s1.  Assumption: Enough space has been allocated 
    for s1 to store the extra characters.
*/
#include <stdio.h>
#include <string.h>

char *append (char *, char *); 

int main () {
   char str1[10];
   char str2[10];

   while (1) { // run forever
      printf ("str1 = ");
      scanf("%s", str1);
      printf ("str2 = ");
      scanf("%s", str2);
      printf ("The new string is %s.\n", append (str1, str2));
   }
   return 0;
}

/*
 * This function appends the characters of s2 to s1 and returns the resulting
 * string.
 */
char* append (char *s1, char *s2) 
{
    int len1 = strlen (s1);
    int len2 = strlen (s2);
    int k;

    for (k = 0; k < len2; k++) {
        s1[k + len1] = s2[k];
    }
    return s1;
}
