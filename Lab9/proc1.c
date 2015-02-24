/* File: proc1.c
 * CPSC-275 Lab9 Exercise 1
 * Author: Hongyi Deng and Kevin Liu
 * Date: Nov 10 2014
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	printf("Hi.\n");
	sleep(10);
	fork();
	sleep(10);
	printf("Bye.\n");
	exit(0);
}
