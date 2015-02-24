/*
 * =====================================================================================
 *
 *       Filename:  myfilecopy1.c
 *
 *    Description:  CPSC-275 Assignment 10 1a
 *
 *        Version:  1.0
 *        Created:  11/25/2014 12:49:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kevin Liu 
 *
 * =====================================================================================
 */

/* Performance table
 * =================
 *
 * Buffer size		Time
 * 1				0.688s
 * 2				0.326s
 * 57				0.019s
 * 128				0.013s
 * 256				0.010s
 * 511				0.009s
 * 513				0.009s
 * 1024				0.008s
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define mode S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: %s <infile> <outfile> <bufsize>\n", argv[0]);
		return 1;
	}
	char *infile = argv[1];
	char *outfile = argv[2];
	size_t bufsize = atoi(argv[3]); 

	char buf[bufsize];
	int fdr, fdw, n;
	
	if ((fdr = open(infile, O_RDONLY, 0)) < 0)
		exit(-1);
	if ((fdw = open(outfile, O_CREAT | O_WRONLY, mode)) < 0)
		exit(-1);
	while ((n = read(fdr, buf, bufsize)) > 0)
		write(fdw, buf, n);
	close(fdr);
	close(fdw);
}

