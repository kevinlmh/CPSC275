/*
   vsm.c: a bare-bones interpretor of Very Simple Machine (VSM) speficiations.
   It interprets each speficiation as given by VSM Language (VSML). VSM
   specification currently supports a flat memory, a single free register, 
   four arithmetic operations, and some primitive branching. The interpreter
   allows the programmer to insert comments in VSM programs -- in each line of
   input, any additional letters that follow the 4-digit number in the front will
   be simply ignored by the interpreter.

   Author: Philip Cho (Hyunsu.Cho@trincoll.edu)
   October 15, 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

#define MAX_MEMORY_SIZE 100
#define MIN_DATA_VAL -9999
#define MAX_DATA_VAL 9999
#define SENTINEL -9999

typedef signed char HALFWORD;
typedef signed short int WORD;
typedef signed int DOUBLEWORD;

// -- Components of a VSM --
// These global variables cannot be accessed from another source file
// thanks to the static keyword. 
static WORD memory[MAX_MEMORY_SIZE]; // flat memory
static int memorySize;
static WORD accumulator = 0; // register
static HALFWORD instructionCounter = 0;
static WORD instructionRegister = 0;
static HALFWORD operationCode = 0;
static HALFWORD operand = 0;

static char rest_of_line[BUFSIZ] = {0};

static void print_usage_and_exit(void);
static int execute_current_instruction(void);
static void produce_computer_dump(void);
static void handle_error(const char *msg);

int main(void)
{
    HALFWORD curloc; // current location number
    DOUBLEWORD curinst; // current instruction inputted
    
    // load program into memory
    curloc = 0; // current location number
    while (1) {
        scanf("%d", &curinst);
        fgets(rest_of_line, BUFSIZ, stdin);
        // Throw out any other following letters -- this mechanism allows for
        // user comments.
        if (curinst == SENTINEL)
            break;
        if (curinst < MIN_DATA_VAL || curinst > MAX_DATA_VAL) {
            printf("*** Value out of range.                   ***\n");
            printf("*** Value must be between %d and +%d ***\n", 
                   MIN_DATA_VAL, MAX_DATA_VAL);
            exit(1);
        }
        memory[curloc] = (WORD)curinst;
        curloc++;
    }

    memorySize = curloc;
    printf("*** Program loading completed ***\n"
           "*** Program execution begins  ***\n");

    if (memorySize > 0) // execute only nonempty program
        while (execute_current_instruction())
            ;

    printf("*** VSM execution terminated ***\n");
    produce_computer_dump();

    return 0;
}

static int execute_current_instruction(void)
/* executes the instruction at the position given by instructionCounter,
 * and then moves the counter appropriately. The counter is incremented by 1
 * unless a branch operation calls for a nonlocal jump. The return value
 * is 1 if there are additional instructions to follow; the return value is 0
 * if the HALT instruction is reached. */
{
    DOUBLEWORD result;

    instructionRegister = memory[instructionCounter];
    if (instructionRegister < 0)
        handle_error("Invalid operation code");

    operationCode = instructionRegister / 100;
    operand = instructionRegister % 100;
    if (operand >= memorySize)
        handle_error("Address out of bounds");

    switch (operationCode) {
        case READ:
            scanf("%d", &result);
            if (result > MAX_DATA_VAL || result < MIN_DATA_VAL)
                handle_error("Data value out of range");
            memory[operand] = (WORD)result;
            instructionCounter++;
            break;
        case WRITE:
            printf("%hd\n", memory[operand]);
            instructionCounter++;
            break;
        case LOAD:
            accumulator = memory[operand];
            instructionCounter++;
            break;
        case STORE:
            memory[operand] = accumulator;
            instructionCounter++;
            break;
        case ADD:
            result = accumulator + memory[operand];
            if (result > MAX_DATA_VAL)
                handle_error("Accumulator overflow");
            accumulator = result; 
            instructionCounter++;
            break;
        case SUBTRACT:
            result = accumulator - memory[operand];
            if (result < MIN_DATA_VAL)
                handle_error("Accumulator overflow");
            accumulator = result;
            instructionCounter++;
            break;
        case DIVIDE:
            if (memory[operand] == 0)
                handle_error("Attempt to divide by zero");
            accumulator /= memory[operand]; 
            instructionCounter++;
            break;
        case MULTIPLY:
            result = (DOUBLEWORD)accumulator * memory[operand];
            if (result > MAX_DATA_VAL || result < MIN_DATA_VAL)
                handle_error("Accumulator overflow");
            accumulator = (WORD)result;
            instructionCounter++;
            break;
        case BRANCH:
            instructionCounter = operand;
            break;
        case BRANCHNEG:
            if (accumulator < 0)
                instructionCounter = operand;
            else
                instructionCounter++;
            break;
        case BRANCHZERO:
            if (accumulator == 0)
                instructionCounter = operand;
            else
                instructionCounter++;
            break;
        case HALT:
            return 0;
            break;
        default:
            handle_error("Invalid operation code");
            break;
    }
    return 1;
}

static void produce_computer_dump(void)
/* outputs a computer dump of the VSM. */
{
    int i, j;
    int ncols = 10;
    int nrows = MAX_MEMORY_SIZE / ncols;
    WORD curval;

    printf("REGISTERS\n");
    printf("accumulator               %+05hd\n", accumulator);
    printf("instructionCounter        %02hhd\n", instructionCounter);
    printf("instructionRegister       %+05hd\n", instructionRegister);
    printf("operationCode             %02hhd\n", operationCode);
    printf("operand                   %02hhd\n", operand);

    printf("\nMEMORY\n");
    printf("  ");
    for (j = 0; j < ncols; j++)
        printf("%6d", j);
    printf("\n");
    for (i = 0; i < nrows; i++) {
        printf("%02d", i * 10);
        for (j = 0; j < ncols; j++) {
            curval = memory[i * ncols + j];
            if (curval >= 0)
                printf(" +%04hd", curval);
            else
                printf(" %05hd", curval);
        }
        printf("\n");
    }
    printf("\n");
}

static void handle_error(const char *msg)
{
    printf("*** %s ***\n", msg);
    printf("*** VSM execution abnormally terminated ***\n");
    produce_computer_dump();
    exit(1);
}
