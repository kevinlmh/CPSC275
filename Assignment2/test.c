#include <stdio.h>

char *array[] = {"one ", "two ", "three ", "four ", "five "};

void mystrcat(char *des, char *src) {
	while (*des != '\0')
		des++;
	while(*src != '\0') {
		*des = *src;
		src++;
		des++;
	}
	*des = '\0';
}

void cat(char *out, int n) {
	if (n >= 0) {
		mystrcat(out, array[n]);
		cat(out, n-1);
	}
}

int main(void) {
	char out[500] = "";
	cat(out, 4);
	printf("%s\n", out);
	int i;
	for (i=0; i<5; i++) {
		printf("%s\n", array[i]);
	}
}
