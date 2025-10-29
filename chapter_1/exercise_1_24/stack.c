
#include "stack.h"


// Stack
typedef struct stack_struct {

    char data;
    unsigned int number_line;
    stack * previous;
} stack;


// Creates a new Stack
stack * stack_new() {

    stack * new_stack = (stack *) malloc(sizeof(stack));
    if (new_stack == NULL)
        return NULL;

    new_stack->previous = NULL;
    new_stack->data = '\0';
    new_stack->number_line = 0;
    return new_stack;
}

// Add value to current stack
void stack_data(stack * stk, char data) {

    stk->data = data;
}

// Print data to current stack
char stack_return_data(stack * stk) {

    return stk->data;
}

// Print line number of the current stack
char stack_return_line_number(stack * stk) {

    return stk->number_line;
}

// Check if previous stack is NULL
char stack_is_end(stack * stk) {

    if (stk->previous == NULL)
        return TRUE;
    return FALSE;
}

// Check if is possible allocating more content
char stack_is_full() {

    stack * test = stack_new();

    if ( test == NULL ) {
        return TRUE;
    }

    free(test);
    return FALSE;
}

// Add new data on the Stack
char stack_push(stack ** stk, char data, unsigned int line) {

    // If There is not more memory to allocate
    if ( stack_is_full() ) {
        return FALSE;
    }

    // If previous is already NULL and data is NULL
    if ( stack_is_end(*stk) && (*stk)->data == '\0') {
        (*stk)->data = data;
        (*stk)->number_line = line;
        return TRUE;
    }

    stack * head = stack_new();
    if ( head == NULL ) {
        return FALSE;
    }
    
    head->previous = *stk;
    head->data = data;
    head->number_line = line;
    *stk = head;
    return TRUE;
    
}

// Remove head data on the Stack
char stack_pop(stack ** stk) {

    if ( stack_is_end(*stk) ) {
        if ( (*stk)->data != '\0' ) {
            (*stk)->data = '\0';
            (*stk)->number_line = 0;
            return TRUE;
        }
        return FALSE;
    }

    stack * old_head = *stk;
    *stk = (*stk)->previous;

    free(old_head);

    return TRUE;
}

void stack_erase(stack ** stk) {

    if ( stack_pop(stk) )
        stack_erase(stk);

}

// Print all values on the Stack
void stack_printlist(stack * stk) {

    printf("{");

    while (stk != NULL) {
        if (stk->previous != NULL)
            printf("%c, ", stk->data);
        else {
            printf("%c", stk->data);
        }
        stk = stk->previous;
    }

    printf("}");
}
