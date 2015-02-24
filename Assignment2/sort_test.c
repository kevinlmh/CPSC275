#include <stdio.h>

void bubbleSort(int array[], int size) {
	int i,j;
	for (i=0; i<size; i++) {
		for (j=0; j<size-1; j++) {
			if (array[j]>array[j+1]) {
				int temp = array[j+1];
				array[j+1] = array[j];
				array[j] = temp;
			}
		}
	}
}

int main(void) {
	int input[100];
	int input_count = 0;
	int i;
	while(scanf("%d", &input[input_count]) != EOF) {
		input_count++;				
	}
	bubbleSort(input, input_count);
	for(i=0; i<input_count; i++) {
		printf("%d\n", input[i]);
	}
}
