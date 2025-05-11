/*
 * Verify that the expression getchar() != EOF is 0 or 1.
 * */


#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF)
        printf(">>> %c is not an EOF, so value is %d\n", c, (c == EOF));
    printf(">>> EOF, so value is %d\n", (c == EOF));
    return 0;
}
