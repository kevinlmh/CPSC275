/*
 * =====================================================================================
 *
 *       Filename:  icsim.c
 *
 *    Description:	CPSC-275 Final Part I 
 *
 *        Version:  1.0
 *        Created:  12/08/2014 01:17:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kevin Liu
 *         
 *    To compile, type the following command in terminal
 *
 *            gcc -o icsim icsim.c
 *
 *    The -DDEBUG flag is available if you want to see debug informations
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>

#define BUF_SIZE 80

// structure to represent a line
struct line {
	long freq;	// frequency
	long tag;	// tag
	char v;		// valid bit
};

// function prototypes
void process_options(int, char **);
void initialize(void);
void cleanup(void);
void load(long);
void printSummary(int, int, int);

// global variables
struct line *cache;		// instruction cache data structure
int E;
int b = 4, B = 16;
char *Evalue = NULL;
char *tvalue = NULL;
int hits = 0;
int misses = 0;
int evictions = 0;
int count = 0;

int main(int argc, char *argv[]) {
	FILE *trace_file;			// file pointer
	char buf[BUF_SIZE];			// assume less than BUF_SIZE chars per line
	char instruction, operation;
	long address, tag;
	int size;
	
	process_options(argc, argv);
	initialize();

	// open read-only
	trace_file = fopen(tvalue, "r"); // open read-only
	if (trace_file == NULL) {
		fprintf(stderr, "Error reading file: %s.\n", tvalue);
	}

	// read line by line
	while (fgets(buf, sizeof(buf), trace_file)) {
		// parse line into operation, address and size
		sscanf(buf, "%c%c %lx,%d", &instruction, &operation, &address, &size);
		// DEBUG CODE
		#ifdef DEBUG
		printf("Instruction: %c, operation: %c, address: %lx, size: %d\n", instruction, operation, address, size);
		#endif

		// decode tag from address
		tag = address >> b;

		// DEBUG
		#ifdef DEBUG
		printf("tag = %lx\n", tag);
		#endif

		if (instruction == 'I') {
			load(tag);
			count++;
		}
	}	

	fclose(trace_file);			// close file
    printSummary(hits, misses, evictions);

	#ifdef DEBUG
	printf("Number of I: %d\n", count);
	#endif

	#ifdef PRINT
	int k;
	for (k = 0; k < E; k++) {
		printf("line %d, v = %d, tag = %ld, freq = %ld\n", k, cache[k].v, cache[k].tag, cache[k].freq);
	}
	#endif

	cleanup();
    return 0;
}

/* 
 * Parse command-line options and arguments
 */
void process_options(int argc, char *argv[]) {
	int index;				// index of command-line arguments
	int opt;				// current command-line option
	opterr = 0;				// set opterr to 0

	while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
		switch (opt) {
			case 'E':
				Evalue = optarg;
				E = atoi(Evalue);
				break;
			case 't':
				tvalue = optarg;
				break;
			case '?':
				if (optopt == 'E') 
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
			default:
				abort();
		}
	}

	// DEBUG CODE
	#ifdef DEBUG
	printf("Evalue = %s, tvalue = %s\n", Evalue, tvalue);
	printf("E = %d\n", E);
	#endif

	// print non-option command-line arguments
	for (index = optind; index < argc; index++)
		fprintf(stderr, "Non-option argument %s\n", argv[index]);

}

/*
 * Create and allocate space for cache data structure
 */
void initialize(void) {
	int i;
	// cache is an array of struct lines
	cache = (struct line *)malloc(sizeof(struct line) * E);
	// initialize each line
	for (i = 0; i < E; i++) {
		cache[i].v = cache[i].tag = cache[i].freq = 0;
	}
}

/*
 * Free allocated spaces and clean up
 */
void cleanup(void) {
	free(cache);
}

/*
 * Load data to CPU
 */
void load(long tag) {
	char isfull = 1;
	int emptyitem;
	int LFUitem = 0;					// least frequently used item (set to first line)
	int LFreq = cache[0].freq;	// least frequency (set to freq of first line)
	int lineindex;
	for (lineindex = 0; lineindex < E; lineindex++) {
		// if line is valid
		if (cache[lineindex].v == 1) {
			// if tag match
			if (cache[lineindex].tag == tag) {
				// cache hit
				hits++;
				// update frequency of current line
				cache[lineindex].freq++;
				return;
			}
			// tag not match
			else {
				// keep track of least frequently used line
				// note that since empty items are selected from the bottom
				// finding the first least frequently used line will give
				// us the oldest one even if there is a tie
				if (cache[lineindex].freq < LFreq) {
					LFUitem = lineindex;
					LFreq = cache[lineindex].freq;
				}
			}
		}
		// if line is not valid 
		else {
			// cache is not full
			isfull = 0;
			// save index of an empty line
			// this cache simulator selects empty from the bottom
			emptyitem = lineindex;
		}
	}
	misses++;	
	if (isfull) {
		#ifdef DEBUG 
		printf("evict line: %d, tag = %ld\n", LFUitem, cache[LFUitem].tag);
		#endif

		// cache is full, evict the LRU line
		cache[LFUitem].tag = tag;
		cache[LFUitem].freq = 1;
		evictions++;
	} else {
		// cache is not full, fetch from DRAM to empty line
		cache[emptyitem].tag = tag;
		cache[emptyitem].v = 1;
		cache[emptyitem].freq = 1;
	}

}

/* 
 * Print summary
 */
void printSummary(int hits, int misses, int evictions) {
	printf("hits: %d, misses: %d, evictions: %d\n", hits, misses, evictions);
}
