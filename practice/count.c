/* a program that counts the number of lines in a text file */
#include <stdio.h>

void usage() {
	fprintf(stderr, "Usage: count [filename]\n");
}

int main(int argc, char* argv[]) {
	char buffer[80];
	if (argc != 2) {
		usage();
	}else {
		FILE *file = fopen(argv[1], "r");
		if (file == NULL) {
			perror("main");
		}else {
			while (fgets(buffer, sizeof(buffer), file) != NULL) {
				puts(buffer);
			}
			fclose(file);
		}
	}
	return(0);
}
