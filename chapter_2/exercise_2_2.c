/*
for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i) 
Write a loop equivalent to the for loop above without using && or ||.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 1024

int main() {

    int i = 0;
    int lim = MAXLENGTH + 1;
    char s[MAXLENGTH + 1] = {0};
    char c;

    printf("Insert your array of chars: ");
    while (i < lim - 1) {
        if ((c = getchar()) == '\n')
            break;
        if (c == '\0')
            break;
        if (c == EOF)
            break;
        
        s[i] = c;
        ++i;
    }

    if (i == 0) {
        printf(">> [EMPTY]\n");
        return EXIT_SUCCESS;
    }

    printf(">> %s.\n", s);

    return EXIT_SUCCESS;
}