/* File: whowc.c
 * CPSC-275 Lab9 Exercise 1
 * Author: Hongyi Deng and Kevin Liu
 * Date: Nov 10 2014
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int fd[2];

	if (pipe(fd) == -1) {
		perror("Pipe");
		exit(1);
	}

	switch(fork()) {
		case -1:
			perror("Fork");
			exit(2);
		case 0:
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execl("/usr/bin/who", "who", (char *)0);
			exit(3);
		default:
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execl("/usr/bin/wc", "wc", (char *)0);
			exit(4);
	}
}
