/*
 * Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses its input a line at a time.
 * */


#include <stdio.h>
#define MAXLINE 1000
#define MIN_PRINT_LENGTH 30

int len;
int max;
char line[MAXLINE];
char longest[MAXLINE];
char reverse_str[MAXLINE];

int getline_t(void);
void copy(void);
void reverse(void);

int main() {
    extern int len, max;
    extern char line[], longest[], reverse_str[];

    max = 0;
    while ((len = getline_t()) > 0) {
        if (len > 0) {
            printf(">> (Original): %s\n", line);
            reverse();
            printf(">> (Reverse): %s\n", reverse_str);
        }
    }

    return 0;
}

int getline_t(void) {
    int c, i;
    extern char line[];

    i=0;
    printf(">>> ");
    while((i < MAXLINE - 2) && (c = getchar()) != '\n'){ 
        if (c != ' ' && c != '\t') {
            printf(">> %d: %c\n", i, c);
            line[i] = c;
            ++i;
        }
    }
    if(c == '\n') {
        line[i] = c;
    } else {
        line[i] = '\n';
        while (getchar() != '\n');
    }

    line[i+1] = '\0';
    return i;
}

void copy(void) {
    int i;
    extern char line[], longest[];
    
    i = 0;
    while((longest[i] = line[i]) != '\0')
        ++i;
}

void reverse(void) {
    int i, j;
    extern char line[], reverse_str[];

    j = 0;

    for(i=0; line[i] != '\0'; ++i);
    for (; i >= 0; --i) {
        if (line[i] != '\n' && line[i] != '\0') {
            reverse_str[j] = line[i];
            ++j;
        }
    }
    reverse_str[++j] = '\n';
    reverse_str[++j] = '\0';
}
