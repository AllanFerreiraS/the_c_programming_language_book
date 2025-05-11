/*
 *Write a program to print all input lines that are longer than 80 characters.
 * */

#include <stdio.h>
#define MAXLINE             1000
#define MAX_PRINT_LINE      10

int getline_t(char line[], int maxline);
void copy_t(char to[], char from[]);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = getline_t(line, MAXLINE)) > 0) {
        if (len >= MAX_PRINT_LINE) {
            printf("Word bigger than %d characters (with %d): %s", MAX_PRINT_LINE, len, line);     
            printf("\n");
        }
    }

    return 0;
}

int getline_t(char line[], int maxline) {
    int c, i;
    printf(">>> ");
    for (i = 0; i < maxline - 2 && (c = getchar()) != '\n'; ++i) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
    } else {
        line[i] = '\n';
        while (getchar() != '\n');
    }

    line[i + 1] = '\0';
    
    return i;
}

