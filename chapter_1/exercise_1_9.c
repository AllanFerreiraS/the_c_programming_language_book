
/* Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.
 *
 */


#include <stdio.h>

int main() {
    int c, blank_count;

    blank_count = 0;
    printf(">>> ");
    while ((c = getchar()) != '\n') {
        if(c == ' ' && blank_count > 0)
            continue;
        else if(c != ' ' && blank_count > 0)
            blank_count = 0;
        else if(c == ' ' && blank_count <= 0)
            ++blank_count;

        putchar(c);
    }
    printf("\n");
     return 0;
}
