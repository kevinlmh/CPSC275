/*
 * File: repeat.c
 * CPSC-275 Lab8 Exercise 0
 * Author: Jason Katz and Kevin Liu
 * Date: Nov 3 2014
 */

#include <stdio.h>

int main(int argc, char *argv[]) {	
	int i;
	if (argc < 3 || argc > 3) {
		printf("Usage: %s n s\n", argv[0]);
		printf("  n: the number of repetitions\n");
		printf("  s: string\n");
	} else {
		for (i = 0; i < atoi(argv[1]); i++) {
			printf("%s\n", argv[2]);
		}
	}
}
