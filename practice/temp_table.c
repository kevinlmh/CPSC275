#include <stdio.h>

int main() {
	int high, low, step;
	printf("high: ");
	scanf("%d", &high);
	printf("low: ");
	scanf("%d", &low);
	printf("step: ");
	scanf("%d", &step);
	printf("\n");
	for(int i=low; i<high; i+=step) {
		int c = (5.0/9.0)*(i-32);
		printf("%d   %d\n", i, c);
	}
	return 0;
}
