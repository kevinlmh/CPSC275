#include <stdio.h>
int str_length;

void mystrcp(char *des, char *src) {
	while (*src != '\0') {
		*des = *src;
			src++;
			des++;
	}
	*des = *src;
}

void remove_char(char *str, int length, int index) {
	int i;
	for (i=index; i<length; i++) {
		*(str+i) = *(str+i+1);
	}
}

void permute(char *str, int length) {
	if (length == 1) {
		printf("%c\n", *str);
		return;
	}
	else {
		int i;
		for (i=0; i<length; i++) {
			char temp[100];
			mystrcp(temp, str);
			printf("%c", *(str+i));
			remove_char(temp, length, i);
			permute(temp, length-1);
		}
	}
}

int numchars(char *str) {
	int count = 0;
	while (*str != '\0') {
		count++;
		str++;
	}
	return count;
}


int main(void) {
	char str[100];
	scanf("%s", str);
	str_length = numchars(str);
	permute(str, str_length);
}
