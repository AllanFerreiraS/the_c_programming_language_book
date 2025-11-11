/*
Exercise 2-3. Write a function htoi(s), which converts a string of 
hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value.
The allowable digits are 0 through 9, a through f, and A through F.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLEN  1024

unsigned int htoi(const char * s) {

    unsigned int decimalval = 0;

    for (int i = 0; s[i] != '\0'; i++) {

        // Ignore 0x and 0X
        if ( (s[i] == '0' && i == 0) || ((s[i] == 'x' || s[i] == 'X') && i == 1) )
            continue;

        if (s[i] >= 'A' && s[i] <= 'F') 
            decimalval = (decimalval * 16) + (s[i] - 'A' + 10);
        else if (s[i] >= 'a' && s[i] <= 'f')
            decimalval = (decimalval * 16) + (s[i] - 'a' + 10);
        else if (s[i] >= '0' && s[i] <= '9')
            decimalval = (decimalval * 16) + (s[i] - '0');
        else
            break;
    }

    return decimalval;
}

int main() {

    char buffer[MAXLEN + 1];
    unsigned int decimal_value = 0;
    printf("Insert a value in Hexadecimal [0x0000, 0X0000 or 0000]: ");
    fgets(buffer, sizeof(buffer), stdin);
    decimal_value = htoi(buffer);
    printf(">> %u", decimal_value);
    return EXIT_SUCCESS;
}