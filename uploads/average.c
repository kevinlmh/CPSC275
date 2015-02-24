/*
 * This program reads a set of values from the user and prints their average.
*/

#include <stdio.h>

int read_values(double);

int main()
{
   double sum=0;
   int values;

   values = read_values(sum);
   printf("Average: %f\n", sum/values);

   return 0;
}

/* 
 * The function reads a set of values from stdin, stores their sum, and
 * returns the number of values read.
 */
int read_values(double sum)
{
   int nValues, input;

   nValues = 0;
   sum = 0.0;

   printf("Enter input values (enter 0 to finish):\n");
   scanf("%d", &input);
   while(input != 0) {
     nValues++;
     sum += input;
     scanf("%d", input);
   }

   return nValues;
}
