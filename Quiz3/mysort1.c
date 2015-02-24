/*
 * Program: mysort1.c
 * Purpose: Sort a list of numbers in an alternating sequence
 * Rewritten based on solution of Quiz 2
 * Author: Kevin Liu
 * Date: 09/22/2014
 */

#include <stdio.h>

#define N 100

int smallest(int *, int, int);
void exchange(int *, int, int);

int main(void)
{
   int num[N];
   int i, loc, count = 0;
   int left, right;

   // input numbers
   while (scanf("%d", num + count) != EOF)
      count++;

   // the entire list
   left = 0;
   right = count - 1;

   for (i = 0; i < count / 2; i++) {
      loc = smallest(num, left, right);
      exchange(num, left, loc);
      left++; // move to the right
      loc = smallest(num, left, right);
      exchange(num, right, loc);
      right--; // move to the left
   }

   for (i = 0; i < count; i++) 
      printf("%d ", *(num + i));
   printf("\n");

   return 0;
}

/*
 * Function: smallest
 * Purpose: Computes the index of the smallest element in the list:
 *   *(arr + begin) to *(arr + end)
 *
 * Parameters: 
 *   arr: pointer to a list of numbers
 *   begin: index of the leftmost element in the list
 *   end: index of the rightmost element in the list
 *
 * Returns: the index of the smallest element
 */
int smallest(int *arr, int begin, int end)
{
   int i, idx = begin, small = *(arr + begin);

   for (i = begin + 1; i <= end; i++) 
      if (*(arr + i) < small) {
         small = *(arr + i);
         idx = i;
      }
   return idx;
}

/*
 * Function: exchange
 * Purpose: Exchanges two elements of an array.                    
 *
 * Parameters: 
 *   arr: pointer to a list of numbers
 *   first: index of the first element 
 *   second: index of the second element
 *
 * Returns: none
 */
void exchange(int *arr, int first, int second)
{
   int temp = *(arr + first);
   *(arr + first)= *(arr + second);
   *(arr + second) = temp;
}