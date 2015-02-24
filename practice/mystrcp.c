#include <stdio.h>

char *mystrcp(char *des, char *src) {
	while(*des != '\0')
		des++;
	for(; *src != '\0'; src++) {
		*des = *src;
		des++;
	}
	*des = '\0';
}

int main(void) {
	char des[20] = "hello";
	char src[] = "world";
	mystrcp(des, src);
	printf("%s\n", des);
}
