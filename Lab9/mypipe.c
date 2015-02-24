/* File: mypipe.c
 * CPSC-275 Lab9 Exercise 1
 * Author: Hongyi Deng and Kevin Liu
 * Date: Nov 10 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 4)
		fprintf(stderr, "Wrong number of arguments!\n");
	char prog[50] = "/usr/bin/";	
	char cmd0[50], cmd1[50], cmd2[50];

	strncpy(cmd0, prog, 50);
	strncpy(cmd1, prog, 50);
	strncpy(cmd2, prog, 50);
	
	char **res[3];
	res[0] = res[1] = res[2] = NULL;

	int idx;
	for (idx = 0; idx < 3; idx++) {
		char *p;
		int n_spaces = 0;
		int i;
		p = strtok(argv[idx+1], " ");
		/* split string and append tokens to 'res' */
		while (p) {
			res[idx] = realloc(res[idx], sizeof (char*) * ++n_spaces);
			if (res[idx] == NULL)
				exit(-1); /* memory allocation failed */
			res[idx][n_spaces-1] = p;
			p = strtok(NULL, " ");
		}
		/* realloc one extra element for the last NULL */
		res[idx] = realloc(res[idx], sizeof (char*) * (n_spaces+1));
		res[idx][n_spaces] = 0;
		// DEBUG PRINT
		//for (i = 0; i < (n_spaces+1); ++i)
			//printf("res[%d][%d] = %s\n", idx, i, res[idx][i]);
	}
	
	strncat(cmd0, res[0][0], 30);
	strncat(cmd1, res[1][0], 30);
	strncat(cmd2, res[2][0], 30);

	// DEBUG PRINT
	//printf("cmd0 = %s, cmd1 = %s, cmd2 = %s\n", cmd0, cmd1, cmd2);

	int fd[2];
	int fd2[2];

	if (pipe(fd) == -1) {
		perror("Pipe");
		exit(1);
	}

	switch(fork()) {
		case -1:
			perror("Fork");
			exit(2);
		case 0:
			if (pipe(fd2) == -1) {
				perror("Pipe");
				exit(3);
			}
			switch(fork()) {
				case -1:
					perror("Fork");
					exit(4);
				case 0:
					dup2(fd2[1], STDOUT_FILENO);
					close(fd2[0]);
					close(fd2[1]);
					execv(cmd0, res[0]);
					exit(5);
				default:
					dup2(fd2[0], STDIN_FILENO);
					dup2(fd[1], STDOUT_FILENO);
					close(fd2[0]);
					close(fd2[1]);
					execv(cmd1, res[1]);
					exit(6);
			}
		default:
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execv(cmd2, res[2]);
			exit(7);
	}

	/* clean up */
	free(res[0]);
	free(res[1]);
	free(res[2]);
}
