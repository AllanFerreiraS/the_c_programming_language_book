/*
 *Write a program that prints its input one word per line.
 * */

#include <stdio.h>

int main() {
    int c;

    while((c = getchar()) != '\n') {
        if(c == ' ')
            putchar('\n');
        else
            putchar(c);
    }
    printf("\n");
}
