

#ifndef EXERCISE_1_24_H
#define EXERCISE_1_24_H

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


#define TRUE            1
#define FALSE           0
#define MAXCHARARRAY    512      //512
#define NORMALMESSAGE   "[Exercise_1_24:]"
#define ERRORMESSAGE    "[Exercise_1_24: Error]"
#define SUCCESSMESSAGE  "[Exercise_1_24: Success]"

// File
typedef struct file_body_struct {

    char * name;
    char * path;
    FILE * body;
    int path_size;
} ex24_file;

char chararr_in_sizenum(char * arr, int size, int * real_size);
char open_file(char * path, ex24_file * file);
char select_file(char * path, ex24_file * file);
char close_file(ex24_file * file);
char read_file(ex24_file * file, char ** feedback);

char open_close_check(char buffer, stack ** pStack, unsigned int line);
void in_word(char buffer, short * ccc, char * in_word, char * result);
void in_scape_sequence(char buffer, short * ccc, char * result);
void in_singlecomment(char buffer, short * scc, char * result);
void in_multiplecomment(char buffer, short * mcc, char * result);

void restart_vars();
void print_help(void);

#endif