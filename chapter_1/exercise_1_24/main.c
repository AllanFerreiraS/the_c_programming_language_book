/*
    Write a program to check a C program for rudimentary syntax errors
    like unmatched parentheses, brackets and braces.
    Don't forget about quotes, both single and double, escape sequences, and comments.
    (This program is hard if you do it in full generality.) 
*/

/*
    Processes:
    [0] Check if file exists, if not, next file until argv ends.                (X)
    [1] Open FILE. Read FILE                                                    (X)
    [1] Check for unmatched parentheses, brackets, braces and quotes.           (X)
    [2] Check for escape sequences \' \" and \\                                 (X)
    [3] Check for comments.                                                     (x)
    [4] Store all feedbacks in a variable                                       (x)
        (ERROR) On File something.c, line X there is something.
    [5] Create a mannual.                                                       ()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercise_1_24.h"

ex24_file main_file = {
    .body =         NULL,
    .name =         NULL,
    .path =         NULL,
    .path_size =    0
};

int main(int argc, char ** argv) {

    // If no parameters
    if (argc <= 1) {
        printf("%s >> O programa deve conter pelo menos 1 caminho para o arquivo a ser analisado.\n", ERRORMESSAGE);
        printf("Use -h para mais detalhes.\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)  {
        print_help();
        return EXIT_SUCCESS;
    }

    // Check for all parameters
    for (int i = 1; i < argc; i++) {

        char * feedback = NULL;

        // Open New File
        if ( select_file(argv[i], &main_file) ) { // If Error
            if ( i < argc - 1) {
                printf("%s >> Procurando próximo arquivo...\n", NORMALMESSAGE);
                continue;
            }
            else {
                return EXIT_FAILURE;
            }
        }

        printf("Caminho do arquivo: %s.\n", main_file.path);

        // Analizing File
        if ( read_file(&main_file, &feedback) ) { // If Error
            printf("EXIT FAILURE\n");
            return EXIT_FAILURE;
        }

        restart_vars();

        // If feedback
        if (feedback != NULL)
            printf("%s\n", feedback);

        // Close Current File
        if ( close_file(&main_file) ) { // If Error
            return EXIT_FAILURE;
        }

        free(feedback);

    }


    return EXIT_SUCCESS;
}