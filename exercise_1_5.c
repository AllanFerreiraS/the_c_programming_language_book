/*
 * Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.
 * */

#include <stdio.h>

int main() {
    float f, c;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Fahrenheit\tCelsius\n");
    for (f = upper; f >= lower; f -= step) {
        c = (5.0/9.0) * (f - 32.0);
        printf("%10.0f\t%7.1f\n", f, c);
    }

    return 0;
}
