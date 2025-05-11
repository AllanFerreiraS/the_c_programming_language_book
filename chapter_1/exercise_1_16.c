/*
 *Revise the main routine of the longest-line program 
 *so it will correctly print the length of arbitrary long input lines, 
 *and as much as possible of the text.
 * */

#include <stdio.h>
#define MAXLINE             1000

int getline_t(char line[], int maxline);
void copy_t(char to[], char from[]);

int main() {
    int len;
    int max;
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

void copy_t(char to[], char from[]) {
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}
