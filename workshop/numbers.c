#include <stdio.h>

char array[100];
int main(void) {
	int i;
	for (i=0; i<100; i++)
		array[i] = 1;
	
	int num;
	while(scanf("%d\n", &num) != EOF) {
		if (num == 0) break;
		array[num-1] = 0;
	}

	int col = 0;
	for (i=0; i<100; i++) {
		if (array[i]) {
			printf("%d ", i+1);
			col++;
			if (col != 0 && col % 10 == 0)
				printf("\n");
		}
	}
	printf("\n");
}
