
/* Write a program to count blanks, tabs, and newlines.
 *
 */


#include <stdio.h>

int main() {
    int c, line_count, tab_count, blank_count;

    line_count = tab_count = blank_count = 0;
    printf(">>> ");
    while ((c = getchar()) != EOF) {
        if (c == '\n'){
            ++line_count;
            printf("%d lines...\n", line_count);
        }
        else if(c == '\t') {
            ++tab_count;
            printf("%d tabs...\n", tab_count);
        }
        else if(c == ' ') {
            ++blank_count;
            printf("%d blanks...\n", blank_count);
        }
    }
     return 0;
}
