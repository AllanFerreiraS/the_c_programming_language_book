/*
 *Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.
 * */


#include <stdio.h>

int fahr_to_cels(int);

int main() {
    float f, c;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Fahrenheit\tCelsius\n");
    for (f = lower; f <= upper; f += step){
        c = fahr_to_cels(f);
        printf("%10.0f\t%7.2f\n", f, c);
    }
}

int fahr_to_cels(int f) {
    return (5.0/9.0) * (f - 32.0);
}
