/* File: proc2.c
 * CPSC-275 Lab9 Exercise 1
 * Author: Hongyi Deng and Kevin Liu
 * Date: Nov 10 2014
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	pid_t pid;
	char *message;
	int i;

	printf("fork program staring\n");
	pid = fork();
	switch(pid) {
		case -1:
			exit(1);
		case 0:
			message = "This is the child";
			break;
		default:
			message = "This is the parent";
			break;
	}

	for (i = 0; i < N; i++)
		puts(message);

	exit(0);
}
