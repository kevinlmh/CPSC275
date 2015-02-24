/*
 * File: calc.c
 * CPSC-275 Lab8 Exercise 1
 * Author: Jason Katz and Kevin Liu
 * Date Nov3 2014
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int op1, op2;
	char operation;
	if (argc != 4) {
		printf("Usage: %s op1 operation op2\n", argv[0]);
		printf("  op1: the first operand\n");
		printf("  operation: an arithmetic operator (+, -, *, /)\n");
		printf("  op2: the second operand\n");
	} else {
		op1 = atoi(argv[1]);
		op2 = atoi(argv[3]);
		operation = *argv[2];
		switch (operation) {
			case '+':
				printf("%d\n", op1 + op2);
				break;
			case '-':
				printf("%d\n", op1 - op2);
				break;
			case '*':
				printf("%d\n", op1 * op2);
				break;
			case '/':
				printf("%d\n", op1 / op2);
				break;
			default:
				printf("Unknown operator!\n");
				break;
		}
	}

}
