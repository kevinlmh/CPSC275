/* 
 * File: good_echo.c
 * CPSC-275 Lab6
 * Author: Jason Katz and Kevin Liu
 * Date: Oct 20 2014
 */

#include <stdio.h>
#include <string.h>

#define SIZE 8

int main(void) {
	char buf[SIZE];
	if (fgets(buf, SIZE, stdin) != NULL) {
			int len = strlen(buf);
			if (buf[len-1] != '\n')
				printf("*** Error: String too long and is truncated! ***\n");
			buf[len-1] = '\0';
			int i;
			for (i=0; i<len; i++) {
				putchar(buf[i]);
			}
			putchar('\n');
	} else {
		printf("*** Error: Empty String! ***\n");
	}
}
