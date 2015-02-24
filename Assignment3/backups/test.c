#include <stdio.h>

int main(void) {
	char text[] = "helloworld\n";
	int i;
	for (i=0; i<10; i++) {
		printf("%x", text[i]);
	}
}

0110010101101000
0110110001101100
0111011101101111
0111001001101111
0110010001101100
0000000000000000
