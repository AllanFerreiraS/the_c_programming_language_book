#ifndef EXERCISE_1_23_SOURCE_H
#define EXERCISE_1_23_SOURCE_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE            1
#define FALSE           0
#define MAXCHARPATH     512      //512
#define MAXCHARARRAY    256      //256
#define AMOUNTCOMMAND   3
#define NORMALMESSAGE   "[Exercise_1_23:]"
#define ERRORMESSAGE    "[Exercise_1_23: Error]"
#define SUCCESSMESSAGE  "[Exercise_1_23: Success]"

typedef struct str_file
{
    char * name;
    char * path;
    char * mode;
    char temp;
    FILE * body;
} ex23_file;

extern ex23_file original_file;
extern ex23_file temp_file;
extern ex23_file new_file;

char select_file(char * path);
char open_file(char * path, char * mode, FILE ** f);
char * generate_name_new_dot_c(ex23_file f);
char create_file(char * name, char * path, char temp, ex23_file * ptr_file);
char copy_file_to_file(ex23_file * from, ex23_file * to);
char close_ex23_body(ex23_file * f);
char change_file_mode(ex23_file * f, char * mode);
char chararr_in_sizenum(char * arr, int size);

char remove_singleline_comments(ex23_file * from, ex23_file * to);
char remove_multiline_comments(ex23_file * from, ex23_file * to);
char save_changes(ex23_file * origin, ex23_file * end);

void delete_file(ex23_file * f);
void man_program();

#endif