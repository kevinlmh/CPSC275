#include <stdio.h>

void swap(int *, int *);

int main(void)
{
	int i = 3;
	int j = 7;

	printf("Before swap(): i = %d, j = %d\n", i, j);
	swap(&i, &j);
	printf("After swap(): i = %d, j = %d\n", i, j);

	return 0;
}

void swap(int *x, int *y)
{
	int temp = *x;

	*x = *y;
	*y = temp;
}
