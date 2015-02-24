/*
 * Program: vsm.c
 * Purpose: This program simulates a simple machine that can execute
 *          Very Simple Machine Language(VSML).
 * Author:  Kevin Liu
 * Date:    9/20/2014
 */

#include <stdio.h>

// instruction table
#define EOC   0x0
#define LOAD  0x1
#define STORE 0x2
#define READ  0x3
#define WRITE 0x4
#define ADD   0x5
#define SUB   0x6
#define MUL   0x7
#define DIV   0x8
#define JUMP  0x9
#define JNEG  0xA
#define JZERO 0xB
#define HALT  0xC
#define NOP1  0xD
#define NOP2  0xE
#define NOP3  0xF

// operation type
#define MEM 0
#define NUM 1

typedef unsigned short UWORD;
typedef short WORD;
void error(char *);
void error_n(char *, UWORD);

// function prototype
void dump(void);

// VSM supports only 2048 bytes (1024 words) of memory
// In this program all memories will be stored as UNSIGNED WORD
// Bud during execution, the DATA section will be treated as SIGNED WORD
// Casting will happen prior to operations on the DATA section
UWORD memory[1024];
WORD accumulator;
UWORD iCounter = 0;
UWORD iRegister;
UWORD opCode;
UWORD opType;
WORD oprand;

int main (void) {

	printf("*** Initializing VSM ***\n");
	// load instructions into memory
	printf("*** Loading instructions into memory ***\n");
	// c is used for counting # of instructions
	// and later store the location of EOC
	int c = 0;

	while (1) {
		int ret = scanf("%hX\n", &memory[c]);
		if (ret == 0)
			error("Illegal opCode");
		if (memory[c] == EOC)
			break;
		if (c >= 1024) {
			printf("*** Cannot execute more than 1024 lines of instructions ***\n");
			printf("*** VSM execution abnormally terminated ***\n");
			dump();
			return 0;
		}
		c++;
	}
	// dump();

	// excute instructions in memory
	while(iCounter < c) {
		// load current instruction into instructionRegister
		iRegister = memory[iCounter];
		// decode instruction
		opCode = iRegister / 0x1000;
		opType = (iRegister % 0x1000) / 0x800;
		oprand = iRegister % 0x800;

		// printf("iRegister: %x\n", iRegister);
		// printf("iCounter: %d\n", iCounter);
		// printf("opCode: %x\n", opCode);
		// printf("opType: %x\n", opType);
		// printf("oprand: %d\n", oprand);

		// check for illegal memory reference
		if (!opType) {
			if (opCode >= LOAD && opCode <= DIV) {
				if (oprand < 1024 || oprand > 2047) {
					error("Illegal memory reference");
					return 1;
				}
			}
			else if (opCode >= JUMP && opCode <= JZERO) {
				if (oprand < 0 || oprand > 1023) {
					error("Illegal memory reference");
					return 1;
				}
			}
		}


		switch(opCode) {
			case EOC:	return 1;
			case LOAD:	accumulator = (opType)? oprand : memory[oprand/2];
						iCounter++;
						break;
			case STORE:	memory[oprand/2] = accumulator;
						iCounter++;
						break;
			case READ:	scanf("%hX\n", &memory[oprand/2]);
						iCounter++;
						break;
			case WRITE:	printf("%d\n", (WORD)memory[oprand/2]);
						iCounter++;
						break;
			case ADD:	accumulator += (opType)? oprand : (WORD)memory[oprand/2];
						iCounter++;
						break;
			case SUB:	accumulator -= (opType)? oprand : (WORD)memory[oprand/2];
						iCounter++;
						break;
			case MUL:	accumulator *= (opType)? oprand : (WORD)memory[oprand/2];
						iCounter++;
						break;
			case DIV:	if (opType) {
							if (oprand == 0) {
								error("Attempt to divide by zero");
								return 1;
							}
							accumulator /= oprand;
						}
						else {
							if (memory[oprand/2] == 0) {
								error("Attempt to divide by zero");
								return 1;
							}
							accumulator /= (WORD)memory[oprand/2];
						}
						//accumulator /= (opType)? oprand : (WORD)memory[oprand/2];
						iCounter++;
						break;
			case JUMP:	iCounter = oprand/2;
						break;
			case JNEG:	iCounter = (accumulator < 0)? oprand/2 : iCounter+1;
						break;
			case JZERO:	iCounter = (accumulator == 0)? oprand/2 : iCounter+1;
						break;
			case HALT:	printf("*** VSM execution terminated ***\n");
						dump();
						return 0;
			case NOP1:	iCounter++;
						break;
			case NOP2:	iCounter++;
						break;
			case NOP3:	iCounter++;
						break;
			default:	error("Illegal opCode");
						return 1;
		}
		// dump();
	}
	
	return 1;
}

void dump() {
	int i, j;
	// print REGISTERS
	printf("REGISTERS:\n");
	printf("accumulator\t\t0x%.4x\n", accumulator);
	printf("instructionRegister\t0x%.4x\n", iRegister);
	printf("instructionCounter\t0x%.4x\n", iCounter * 2);
	printf("opCode\t\t\t0x%.1x\n", opCode);
	printf("oprand\t\t\t0x%.4x\n", oprand);

	// print CODE
	printf("\nCODE:\n");
	printf("     0  1  2  3  4  5  6  7  8  9\n");
	for (i = 0; i < 50; i += 5) {
		printf("%.4d ", 2 * i);
		for (j = 0; j < 5; j++) {
			printf("%.2x %.2x ", memory[i + j] / 0x100, memory[i + j] % 0x100);
		}
		printf("\n");
	}
	printf("\n...\n");

	// print DATA
	printf("\nDATA:\n");
	printf("     0  1  2  3  4  5  6  7  8  9\n");
	for (i = 512; i < 557; i += 5) {
		printf("%.4d ", 2 * i);
		for (j = 0; j < 5; j++) {
			printf("%.2x %.2x ", memory[i + j] / 0x100, memory[i + j] % 0x100);
		}
		printf("\n");
	}
	printf("\n...\n");
}

void error(char *msg) {
	printf("***  %s ***\n", msg);
	printf("*** VSM execution abnormally terminated ***\n");
	dump();
}




















