/*
 *Write a program detab that replaces tabs in the input with the proper number 
 *of blanks to space to the next tab stop. 
 *Assume a fixed set of tab stops, say every n columns. 
 *Should n be a variable or a symbolic parameter?
 * */

#include <stdio.h>
#define TAB_COLLUM      8
#define MAXLINE         1000

int main() {
    
    int c, i, tab_next_stop;
    char input[MAXLINE];


    i = tab_next_stop = 0;

    for (int j = 0; j < MAXLINE; j++)
        input[j] = '\0';
    
    while(i < MAXLINE - 2 && (c = getchar()) != '\n') {
        if (c == '\t') {
            tab_next_stop = TAB_COLLUM - (i % TAB_COLLUM);
            for (int j = 0; j < tab_next_stop; j++) {
                if (i < MAXLINE - 2) {
                    input[i] = ' ';
                    ++i;
                }
            }
        }
        else {
            input[i] = c;
            ++i;
        }
    }

    input[i] = '\n';
    
    if (i > 0)
        printf("%s", input);

    return 0;    
}

