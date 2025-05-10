

/*
 * Write a program to print the corresponding Celsius to Fahrenheit table.
 * */

#include <stdio.h>

int main() {
    float f, c;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    c = lower;
    printf("Celsius\tFahrenheit\n");
    while (c <= upper) {
        f = (c * 1.8) + 32.0;
        printf("%7.0f\t%10.1f\n", c, f);
        c += step;
    }
}
