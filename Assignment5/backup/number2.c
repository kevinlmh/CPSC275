/* number.s in C language
   just for reference and clearing my thoughts
*/
#include <stdio.h>

// function prototypes
int tentopower(int);
char* int2str(int, char*);

int main(void) {
	char buffer[10];
	int num;
	printf("Enter an integer: ");
	scanf("%d", &num);
	printf("The numeric string equivalent to %d is ", num);

	if (num == 0)
		printf("0");
	if (num < 0) {
		printf("-");
		num = -num;
	}
	int2str(num, buffer);
	
	int i;
	int significant = 0;
	for (i = 0; i < 10; i++) {
		if (significant == 0) {
			if (*(buffer + i) != '0') {
				printf("%c", *(buffer + i));
				if (i % 3 == 0 && i != 9)
					printf(",");
				significant = 1;
			}
		} else {
			printf("%c", *(buffer + i));
			if (i % 3 == 0 && i != 9)
				printf(",");
		}
	}
	printf(".\n");
}

int tentopower(int p) {
	int t = 1;
	for (p; p > 0; p--) {
		t *= 10;
	}
	return t;
}

char* int2str(int num, char *buffer) {
	int i;
	for (i = 0; i < 10; i++) {
		int d = (num / tentopower(i)) % 10;
		*(buffer + 9-i) = '0' + d;
	}
	return buffer;
}
