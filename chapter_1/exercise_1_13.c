/*
 *Write a program to print a histogram of the lengths of words in its input. 
 *It is easy to draw the histogram with the bars horizontal; 
 *a vertical orientation is more challenging
 * */

#include <stdio.h>
#define GRAPH_HEAD_SPACE    15
#define IN                  1
#define OUT                 0

int main() {
    int c, len, in_out;
    len = 0;
    in_out = OUT;
    

    while (1) {
        c = getchar();

        if (c != ' ' && c != '\n') {
            if (in_out == OUT)
                in_out = IN;
            if (len < GRAPH_HEAD_SPACE)
                putchar(c);
            ++len;
        }
        else {
            if (in_out == IN)
                in_out = OUT;
            else if (c != '\n')
                continue;
            else
                break;

            if (len < GRAPH_HEAD_SPACE) {
                for (int i = len; i < 15; i++)
                    printf(" ");
            }
            printf("\t");
            for (int i = 0; i < len; i++)
                printf("|");
            printf(" %d\n", len);
            len = 0;
        }

        if (c == '\n')
            break;
    }

    return 0;
}
