/*
 *Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines.
 * */

/*
 *Revise the main routine of the longest-line program 
 *so it will correctly print the length of arbitrary long input lines, 
 *and as much as possible of the text.
 * */

#include <stdio.h>
#define MAXLINE             1000
#define IN                  1
#define OUT                 0

int getline_t(char line[], int maxline);
void copy_t(char to[], char from[]);
int in_out = OUT;

int main() {
    int len;
    int max;
    extern int in_out;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getline_t(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy_t(longest, line);
        }
    }

    if (max > 0)
        printf("%s", longest);

    return 0;
}

int getline_t(char line[], int maxline) {
    int c, i;
    i = 0;
    extern int in_out;

    printf(">>> ");
    while (i < maxline - 2 && (c = getchar()) != '\n') {
        if (c == ' ' && in_out == IN)
            in_out = OUT;
        else if (c != ' ' && c != '\t') {
            if (in_out == OUT)
                in_out = IN;
            line[i] = c;
            ++i;
        }
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

void copy_t(char to[], char from[]) {
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}
