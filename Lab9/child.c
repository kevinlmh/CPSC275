/* File: child.c
 * CPSC-275 Lab9 Exercise 1
 * Author: Hongyi Deng and Kevin Liu
 * Date: Nov 10 2014
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Process[%d] : child in execution ...\n", getpid());
	sleep(5);
	printf("Process[%d] : child in execution ...\n", getpid());
	exit(0);
}
