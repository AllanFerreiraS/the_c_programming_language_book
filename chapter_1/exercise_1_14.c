/*
 *Write a program to print a histogram of the frequencies of different characters in its input.
 * */

#include <stdio.h>
#define ARR_SIZE 36

int get_maxvalue(int *, int);

int main() {
    int c, dif;

    // alph: alphabet values from 0 to 25, last indexes are for numbers values
    int alph[ARR_SIZE];
    int max;
    
    dif = 'a' - 'A';

    for (int i = 0; i < ARR_SIZE; i++)
        alph[i] = 0;

    printf(">>> ");
    while ((c = getchar()) != '\n') {
        if (c >= 'a' && c <= 'z')
            c = (c - dif);
        if (c >= 'A' && c <= 'Z')
            ++alph[c - 'A'];
        else if (c >= '0' && c <= '9')
            ++alph[26 + (c - '0')];
    }
    printf("\n");


    for (int i = 0; i < ARR_SIZE; i++) {
        if (alph[i] > 0) {
            if (i <= 25)
                printf("%c\t", 'A' + i);
            else if (i > 25)
                printf("%c\t", '0' + (i - 26));
            for (int j = 0; j < alph[i]; j++)
                printf("|");
            printf("\t\t%d\n", alph[i]);
        }
    }

    max = get_maxvalue(alph, ARR_SIZE);
    if (max <= 0)
        return 0;
    
    printf("\n\n");
    for (int i = 0; i < ARR_SIZE; i++)
        if (alph[i] > 0)
            printf("%d\t", alph[i]);
    printf("\n");
    for (int i = max; i > 0; i--) {
        for (int j = 0; j < ARR_SIZE; j++) {
            if (alph[j] >= i && alph[j] > 0)
                printf("||\t");
            else if (alph[j] > 0)
                printf("  \t");
        }
        printf("\n");
    }
    for (int i = 0; i < ARR_SIZE; i++)
        if (alph[i] > 0)
            printf("________");
    printf("\n");
    for (int i = 0; i < ARR_SIZE; i++)
        if (alph[i] > 0)
            if (i <= 25)
                printf("%c\t", 'A' + i);
            else if (i > 25)
                printf("%c\t", '0' + (i - 26));
    printf("\n");
   
}

int get_maxvalue(int * v, int size) {
    
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (v[i] > max)
            max = v[i];
    }

    return max;
}
