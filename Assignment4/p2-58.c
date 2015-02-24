/* File: p2-58.c
 * Author: Kevin Liu
 * Data: Oct 6 2014
 */

#include <stdio.h>

// function prototype
int is_little_endian(void);

int main(void) {
	printf("%s\n", is_little_endian()?
				"I'm on a little-endian machine." :
				"I'm on a big-endian machine.");	
}

int is_little_endian() {
	short w = 0x1;
	if ( *((char *)&w) == 1 )
		return 1;
	else
		return 0;
}
