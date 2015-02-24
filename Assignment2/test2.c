#include <stdio.h>

void mystrcp(char *des, char *src) {
	while (*src != '\0') {
		*des = *src;
		src++;
		des++;
	}
	*des = *src;
}

char *mystrcat(char *des, char *src) {
	char temp_array[100];
	char *temp = temp_array;
	mystrcp(temp, src);
	char *des1 = des;
	while (*des1 != '\0')
		des1++;
	while (*temp != '\0') {
		*des1 = *temp;
		temp++;
		des1++;
	}
	*des1 = '\0';
	return des;
}


int main(void) {
	char string[100] = "hello -";
	mystrcat(string, string);
	mystrcat(string, string);
	printf("%s\n", string);
}
