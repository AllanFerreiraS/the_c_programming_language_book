/*
* Write a program to ``fold'' long input lines into two or more shorter lines after the last 
* non-blank character that occurs before the n-th column of input. Make sure your program does
* something intelligent with very long lines, and if there are no blanks or tabs before the specified column.
*/


#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH	10000
#define	LINE_MAXLENGTH	50
#define IN_WORD		1
#define OUT_WORD	0

char file_content[MAXLENGTH];
FILE *old_fileptr = NULL;
FILE *new_fileptr = NULL;
const char * old_file = NULL;
const char * new_file = "formatted_file.txt";

int main (int argc, char ** argv) {
	
	if (argc <= 1) {
		printf("No file fould.\n");
		printf("Sintax of the program: ./program <file>.<extension>\n");
		printf("This program only takes one file as parameter. Yeah... Thats it! :)\n");
		return EXIT_FAILURE;
	}

	// File
	old_file = argv[1];
 
	int lines = 0;
	int c_counter = 0;
	int in_out = OUT_WORD;

	old_fileptr = fopen(old_file, "r");
	if (old_fileptr == NULL) {
		printf("Occurred an error while trying to open \'%s\'.\n", old_file);
		return EXIT_FAILURE;
	}

	new_fileptr = fopen(new_file, "w");
	if (new_fileptr == NULL) {
		printf("Occurred an error while trying to open \'%s\'.\n", new_file);
		return EXIT_FAILURE;
	}

	fprintf(new_fileptr, ">>>\n>>> FORMATTED FILE\n>>>\n\n");
	
	while ( fgets(file_content, MAXLENGTH, old_fileptr) != NULL) {
		
		file_content[MAXLENGTH - 2] = '\n';
		file_content[MAXLENGTH - 1] = '\0';

		for (int i = 0; (file_content[i]) != '\n'; ++i) {
			if ( (file_content[i] == ' ' || file_content[i] == '\t') && in_out == IN_WORD)
				in_out = OUT_WORD;
			else if ( (file_content[i] != ' ' && file_content[i] != '\t') && in_out == OUT_WORD)
				in_out = IN_WORD;

			// printf("%c", file_content[i]);
			fprintf(new_fileptr, "%c", file_content[i]);
			if (c_counter >= LINE_MAXLENGTH - 1) {
				if (in_out == IN_WORD) {
					fprintf(new_fileptr, "-\n");
					// printf("-\n");
				}
				else {
					fprintf(new_fileptr, "\n");
					// printf("\n");
				}
				c_counter = 0;
			}
			++c_counter;
		}
		// printf("\n");
		fprintf(new_fileptr, "\n");
		++lines;
		c_counter = 0;
	}
	fclose(new_fileptr);
	fclose(old_fileptr);

	return EXIT_SUCCESS;
}
