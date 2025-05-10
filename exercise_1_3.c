/*
 * Modify the temperature conversion program to print a heading above the table.
 * */

#include <stdio.h>

int main() {
    float f, c;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    f = lower;
    printf("Fahrenheit\tCelsius\n");
    while (f <= upper) {
        c = (5.0/9.0) * (f - 32.0);
        printf("%10.0f\t%7.1f\n", f, c);
        f += step;
    }
}
