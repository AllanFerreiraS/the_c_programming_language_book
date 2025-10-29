#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

#define TRUE    1
#define FALSE   0
#define ERRORSTACKMESSAGE    "[Stack: Error]"
#define SUCCESSSTACKMESSAGE  "[Stack: Success]"


// struct
typedef struct stack_struct stack;

stack * stack_new();
void stack_data(stack * stk, char data);
char stack_return_data(stack * stk);
char stack_return_line_number(stack * stk);
char stack_is_end(stack * stk);
char stack_is_full();
char stack_push(stack ** stk, char data, unsigned int line);
char stack_pop(stack ** stk);
void stack_erase(stack ** stk);
void stack_printlist(stack * stk);



#endif