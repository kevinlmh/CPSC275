/*
 * File: mywc.c
 * CPSC-275 Lab8 Exercise 2
 * Author: Jason Katz and Kevin Liu
 * Date: Nov 3 2014
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void printUsage(char *);

int main(int argc, char*argv[]) {
	int  opt;
	char cflag = 0;
	char lflag = 0; 
	char wflag = 0;
	char Lflag = 0;
	char stdin_flag = 0;
	FILE *input_file;
	char *file_name = NULL;
	long long char_count = 0;
	long long line_count = 0;
	long long word_count = 0;
	long long longest = 0;

	if (argc < 2 || argc > 6) {
		printf("Too many arguments.\n");
		printUsage(argv[0]);
		exit(1);
	}
	while ((opt = getopt(argc, argv, "clwL")) != -1) {
		switch (opt) {
			case 'c':
				cflag = 1;
				break;
			case 'l':
				lflag = 1;
				break;
			case 'w':
				wflag = 1;
				break;
			case 'L':
				Lflag = 1;
				break;
			case '?':
				printUsage(argv[0]);
				exit(1);
			default:
				printf("Unknown option: %c\n", opt);
				printUsage(argv[0]);
				exit(1);
		}
	}

	if (optind < argc) {
		file_name = argv[optind];
	} else {
		stdin_flag = 1;
	}

	//printf("cflag = %d, lflag = %d, wflag = %d, Lflag = %d, file_name: %s, stdin_flag = %d\n", cflag, lflag, wflag, Lflag, file_name, stdin_flag);

	if (!stdin_flag) {
		input_file = fopen(file_name, "r");
	} else {
		input_file = stdin;
	}

	char c;
	long long line_len = 0;
	while (1) {
		c = fgetc(input_file);
		char_count++;
		line_len++;
		if (c == ' ')
			word_count++;
		if (c == '\n') {
			longest = ((line_len > longest)? line_len : longest);
			line_len = 0;
			word_count++;
			line_count++;
		}
		if (c == EOF) {
			char_count--;
			break;
		}
	}

	if (cflag)
		printf("Number of characters: %lld\n", char_count);
	if (lflag)
		printf("Number of lines: %lld\n", line_count);
	if (wflag)
		printf("Number of words: %lld\n", word_count);
	if (Lflag)
		printf("Length of the longest line: %lld\n", longest);

	if (input_file != stdin)
		fclose(input_file);

}

void printUsage(char *name) {
	printf("Usage: %s [option] [filename]\n", name);
	printf("  -c  print the number of characters\n");
	printf("  -l  print the number of lines\n");
	printf("  -w  print the number of words\n");
	printf("  -L  print the length of the longest line\n");
}
