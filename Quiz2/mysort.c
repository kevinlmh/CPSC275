#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void mysort(int a[], int size) {
	int i,j;
	int left = 0;
	int right = size-1;
	int index_min;
	for (i=0; i<size; i++) {
		index_min = left;
		for (j=left; j<=right; j++) {
			if (a[j] < a[index_min]) {
				index_min = j;
			}
		}
		if (i % 2 == 0) {
			if (index_min != left) {
			 	swap(&a[index_min], &a[left]);
			}
			left++;
		}
		else {
			if (index_min != right) {
				swap(&a[index_min], &a[right]);
			}
			right--;
		}
	}
}


int main(void)
{
	int input[100];
	int input_count = 0;
	int i;

	while (scanf("%d", &input[input_count]) != EOF) {
		input_count++;
	}

	mysort(input, input_count);

	for (i=0; i<input_count; i++) {
		printf("%d ", input[i]);
	}
	printf("\n");

	return 0;
}