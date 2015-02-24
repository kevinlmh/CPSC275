/*
 * =====================================================================================
 *
 *       Filename:  reversefile.c
 *
 *    Description:  CPSC-275 Assignment 10 2
 *
 *        Version:  1.0
 *        Created:  11/25/2014 08:22:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kevin Liu
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 4096

#define mode S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH

int main(int argc, char *argv[]) {
	char buf[BUFSIZE];	//buffer for one line
	int fdr, fdw;		//file descriptors
	int lc = 0;
	long infilesize = 0, offset = 0;
	char c[1];

	if (argc != 3) {
		write(STDOUT_FILENO, "Usage: ./reversefile <infile> <outfile>\n", 40);
		return 1;
	}
	fdr = open(argv[1], O_RDONLY, 0);
	fdw = open(argv[2], O_CREAT |O_TRUNC | O_WRONLY, mode);		

	/* Determine input file size */
	infilesize = lseek(fdr, 0, SEEK_END);
	/* Jump to input file size byte of output file */
	long temp = lseek(fdw, infilesize, SEEK_SET);
	/* Jump back to the beginnning of input file */
	lseek(fdr, 0, SEEK_SET);

	while(read(fdr, c, 1) > 0) {
		if (lc == BUFSIZE) {
			write(STDOUT_FILENO, "Each line should contain 4096 or less characters.\n", 50);
			return 1;
		}
		if (c[0] == '\n') {
			buf[lc] = '\n';
			lc++;
			/* Jump to appropriate place in outfile */
			lseek(fdw, -lc, SEEK_CUR);
			/* Write content in buffer */
			write(fdw, buf, lc);
			/* Recalculate offset */
			offset -= lc;
			/* Set cursor to current beginnig of contents in outfil */
			lseek(fdw, offset, SEEK_END);
			/* Reset lc to zero */
			lc = 0;
		} else {
			buf[lc] = c[0];
			lc++;
		}
		
	}
	
	close(fdr);
	close(fdw);
}
