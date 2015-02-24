/*
 * =====================================================================================
 *
 *       Filename:  tree.c
 *
 *    Description:  CPSC-275 Lab 12
 *    				A program that mimics tree command of DOS in Linux
 *
 *        Version:  1.0
 *        Created:  12/01/2014 01:29:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:	Soham Madnani & Kevin Liu 	 
 *
 * =====================================================================================
 */


#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void displayDir(char *, int);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <dirname>\n", argv[0]);
		return 1;
	}
	
	displayDir(argv[1], 0);

}

void displayDir(char *dirname, int indentvalue) {
	DIR	*dirpointer = opendir(dirname);
	struct dirent *curdirent;
	char slash = '/';
	while ((curdirent = readdir(dirpointer)) != NULL) {
		char subdirname[1000];
		strncpy(subdirname, dirname, 1000);
		strncat(subdirname, &slash, 1);
		if (curdirent->d_type == DT_DIR) {
			if ( (strcmp(curdirent->d_name, ".") != 0) && (strcmp(curdirent->d_name, "..") != 0) ) {
				int i;
				for (i = 0; i < indentvalue; i++)	printf(" ");
				printf("%s\n", curdirent->d_name);
				strncat(subdirname, curdirent->d_name, 256); 
				displayDir(subdirname, indentvalue + 3);
			}
		}
		else if (curdirent->d_type == DT_REG) {
			int i;
			for (i = 0; i < indentvalue; i++)	printf(" ");
			printf("%s\n", curdirent->d_name);
		}
	}
	closedir(dirpointer);
}
