/* File: csim.c
 * CPSC-275 Assignment 8 Part A
 * Author: Kevin Liu
 * Date: Nov 9 2014
 */
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#define BUF_SIZE 80

// function prototypes
void process_options(int, char **);
void initialize(void);
void load(int, int);
void store(int, int);
void modify(int, int);
void cleanup(void);
void printUsage(char *);

// structure to represent a line
struct line {
	long LAT;			// latest access time
	int tag;
	char v;
};

// global variables
struct line **cache;		// cache data structure	
char hflag = 0;				// flags for command-line options
char vflag = 0;
int s, E, b, S;
char *svalue = NULL;		// arguments for options s, E, b, t
char *Evalue = NULL;
char *bvalue = NULL;
char *tvalue = NULL;
int hits = 0;				// counters for hit, miss and eviction
int misses = 0;
int evictions = 0;
long clocktime = 0;


int main(int argc, char *argv[]) {
	FILE *trace_file;			// file pointer
	char buf[BUF_SIZE];			// assume less than BUF_SIZE chars per line
	char instruction, operation;
	int address, size, setindex, tag;
	
	process_options(argc, argv);
	initialize();
	
	if (hflag)
		printUsage(argv[0]);

	// open read-only
	trace_file = fopen(tvalue, "r"); // open read-only
	if (trace_file == NULL) {
		fprintf(stderr, "Error reading file: %s.\n", tvalue);
	}
	// read line by line
	while (fgets(buf, sizeof(buf), trace_file)) {
		// DEBUG CODE
		//if (vflag)
			//printf("\n%s", buf);
		// parse line into operation, address and size
		sscanf(buf, "%c%c %x,%d", &instruction, &operation, &address, &size);
		// DEBUG CODE
		//printf("operation: %c, address: %x, size: %d\n", operation, address, size);
		// decode set index from address
		setindex = (address >> b) & ((1 << s) - 1); 
		// decode tag from address
		//tag = (address >> (b + s)) & ((1 << (s + b)) - 1);
		tag = address >> ( b + s);
		// DEBUG
		//printf("set index = %d, tag = %d\n", setindex, tag);
		switch (operation) {
			case 'L':
				load(setindex, tag);
				break;
			case 'S':
				store(setindex, tag);
				break;
			case 'M':
				modify(setindex, tag);
				break;
			//default:
				//fprintf(stderr, "Unknown operation: %c.\n", operation);
				//return 1;
		}
	}	

	fclose(trace_file);			// close file
    printSummary(hits, misses, evictions);
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
			case 'h':
				hflag = 1;
				//printUsage();
				break;
			case 'v':	
				vflag = 1;
				break;
			case 's':
				svalue = optarg;
				s = atoi(svalue);
				break;
			case 'E':
				Evalue = optarg;
				E = atoi(Evalue);
				break;
			case 'b':
				bvalue = optarg;
				b = atoi(bvalue);
				break;
			case 't':
				tvalue = optarg;
				break;
			case '?':
				if (optopt == 's' || optopt == 'E' ||
					optopt == 'b' || optopt == 't'  )
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
	//printf("hflag = %d, vflag = %d, svalue = %s, Evalue = %s, bvalue = %s, tvalue = %s\n", hflag, vflag, svalue, Evalue, bvalue, tvalue);
	//printf("s = %d, E = %d, b = %d\n", s, E, b);
	// print non-option command-line arguments
	for (index = optind; index < argc; index++)
		fprintf(stderr, "Non-option argument %s\n", argv[index]);

}

/*
 * Create and allocate space for cache data structure
 */
void initialize(void) {
	S = 2 << s;				// S = 2^s
	int i, j; 
	// an array of pointers to array of struct line
	// yes I know it's confusing
	cache = (struct line **)malloc(sizeof(struct line *) * S);
	// initialize each pointer in sets
	for (i = 0; i < S; i++) {
		cache[i] = (struct line *)malloc(sizeof(struct line) * E);
		for (j = 0; j < E; j++)
			cache[i][j].v = cache[i][j].tag = cache[i][j].LAT = 0;
	}
}

/*
 * Free allocated spaces and clean up
 */
void cleanup(void) {
	int i;
	for (i = 0; i < S; i++) {
		free(cache[i]);
	}
	free(cache);
}

/*
 * Load data to CPU
 */
void load(int setindex, int tag) {
	char isfull = 1;
	int emptyitem;
	int LRUitem = 0;					// least recently used item (set to first line)
	int LRAT = cache[setindex][0].LAT;	// least recent access time (set to LAT of first line)
	int lineindex;
	for (lineindex = 0; lineindex < E; lineindex++) {
		// if line is valid
		if (cache[setindex][lineindex].v == 1) {
			//if (vflag)	printf("line valid\n");
			// if tag match
			if (cache[setindex][lineindex].tag == tag) {
				if (vflag)	printf("load hit\n");
				// cache hit
				hits++;
				// update LAT of current line
				//cache[setindex][lineindex].LAT = clock();
				cache[setindex][lineindex].LAT = ++clocktime;
				return;
			}
			// tag not match
			else {
				//if (vflag)	printf("tag not match\n");
				// keep track of least recently used line
				if (cache[setindex][lineindex].LAT < LRAT) {
					LRUitem = lineindex;
					LRAT = cache[setindex][lineindex].LAT;
				}
			}
		}
		// if line is not valid 
		else {
			//if (vflag)	printf("line not valid\n");
			// cache is not full
			isfull = 0;
			// save index of an empty line
			emptyitem = lineindex;
		}
	}

	//if (vflag)	printf("miss ");
	misses++;	
	if (isfull) {
		// cache is full, evict the LRU line
		cache[setindex][LRUitem].tag = tag;
		//cache[setindex][LRUitem].LAT = clock();
		cache[setindex][LRUitem].LAT = ++clocktime;
		evictions++;
		//if (vflag)	printf("evict ");
	} else {
		// cache is not full, fetch from DRAM to empty line
		cache[setindex][emptyitem].tag = tag;
		cache[setindex][emptyitem].v = 1;
		//cache[setindex][emptyitem].LAT = clock();
		cache[setindex][emptyitem].LAT = ++clocktime;
	}

}

/*
 * Store data
 */
void store(int setindex, int tag) {	
	int lineindex;

	for (lineindex = 0; lineindex < E; lineindex++) {
		// if line is valid and tag match
		if (cache[setindex][lineindex].v == 1 && cache[setindex][lineindex].tag == tag) {
			// cache hit
			hits++;
			//if (vflag)	printf("hit ");
			// update LAT of current line
			//cache[setindex][lineindex].LAT = clock();
			cache[setindex][lineindex].LAT = ++clocktime;
			return;
		}
	}

	// cache miss
	load(setindex, tag);
}

/*
 * Modify data (load and store)
 */
void modify(int setindex, int tag) {
	load(setindex, tag);
	store(setindex, tag);
}

/*
 * Print usage information
 */
void printUsage(char *filename) {
	printf("Usage: %s [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n", filename);
	printf("  -h: Help flag that prints usage info\n");
	printf("  -v: Verbose flag than displays trace info\n");
	printf("  -s <s>: Number of set index bits\n");
	printf("  -E <E>: Associativity (number of lines per set)\n");
	printf("  -b <b>: Number of block bits\n");
	printf("  -t <tracefile>: Name of the valgrind trace to replay\n");
}
