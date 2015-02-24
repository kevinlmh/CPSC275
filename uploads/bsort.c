/* Bubble sort */
 
#include <stdio.h>

#define N 10
 
void bsort(int a[], int n);

int main()
{
  int num[N] = {35, 4, 1, 5, 6, 23, 2, 11, 22, 3};
  int i;
 
  printf("before sort:\n");
  for (i = 0 ; i < N ; i++ )
     printf("%d\n", num[i]);

  bsort(num, 10);
  printf("\nafter sort:\n");
  for (i = 0 ; i < N ; i++ )
     printf("%d\n", num[i]);

  return 0;
}

void bsort(int a[], int n)
{
  int i, j, temp;

  for (i = 0 ; i < n-1; i++)
  {
    for (j = 0 ; j < n-i-1; j++)
    {
      if (a[j] > a[j+1]) 
      {
        temp = a[j];
        a[j] = a[j+1];
        a[j+1] = temp;
      }
    }
  }
}
