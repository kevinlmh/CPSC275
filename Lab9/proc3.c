/* File: proc3.c
 * CPSC-275 Lab9 Exercise 1
 * Author: Hongyi Deng and Kevin Liu
 * Date: Nov 10 2014
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	pid_t pid;

	printf("fork program staring\n");
	pid = fork();
	switch(pid) {
		case -1:
			exit(1);
		case 0:
			execl("child", "child", (char *)0);
			exit(1);
		default:
			printf("Process[%d] : parent in execution ...\n", getpid());
			sleep(5);
			if (wait(NULL) > 0) /* waiting for child */
				printf("Process[%d] : parent terminating child ...\n", getpid());
			exit(0);
	}

}

