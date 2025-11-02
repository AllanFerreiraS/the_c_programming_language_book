/*
    Exercise 2-1. Write a program to determine the ranges of char, short, int, and long variables,
    both signed and unsigned, by printing appropriate values from standard headers and by direct computation.
    Harder if you compute them: determine the ranges of the various floating-point types.
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define BYTE_LENGTH         8
#define INVERTER            (~0)
#define MAX(BIT_LENGTH)     (~(1UL << BIT_LENGTH))
#define MIN(BIT_LENGTH)     (1UL << BIT_LENGTH)


// Chars
#define EX_2_1_UCHAR        (unsigned char)     INVERTER
#define EX_2_1_CHAR_MAX     (signed char)       MAX(BYTE_LENGTH - 1)
#define EX_2_1_CHAR_MIN     (signed char)       MIN(BYTE_LENGTH - 1)

#define EX_2_1_USHORT       (unsigned short)    INVERTER
#define EX_2_1_SHORT_MAX    (signed short)      MAX( (BYTE_LENGTH * 2) - 1 )
#define EX_2_1_SHORT_MIN    (signed short)      MIN( (BYTE_LENGTH * 2) - 1 )

#define EX_2_1_UINT         (unsigned int)      INVERTER
#define EX_2_1_INT_MAX      (signed int)        MAX( (BYTE_LENGTH * 4) - 1 )
#define EX_2_1_INT_MIN      (signed int)        MIN( (BYTE_LENGTH * 4) - 1 )

#define EX_2_1_ULONG        (unsigned long)     INVERTER
#define EX_2_1_LONG_MAX     (signed long)       MAX( (BYTE_LENGTH * 8) - 1 )
#define EX_2_1_LONG_MIN     (signed long)       MIN( (BYTE_LENGTH * 8) - 1 )



int ex_2_1_sizeof(char * datatype) {

    unsigned long value = 0;
    unsigned int bit_count = 0;

    if ( (strcmp(datatype, "char") == 0) ) 
        value = (long) EX_2_1_UCHAR;
    else if ( (strcmp(datatype, "short") == 0) )
        value = (long)  EX_2_1_USHORT;
    else if ( (strcmp(datatype, "int") == 0) )
        value = (long)  EX_2_1_UINT;
    else if ( (strcmp(datatype, "long") == 0) )
        value = EX_2_1_ULONG;
    else
        return 0;

    while ( (value = (value >> 1)) > 0 )
        bit_count++;
    bit_count++;
    
    return bit_count / 8;
}

int main() {

    printf(">> Unsigned Char:\t%d\n", EX_2_1_UCHAR, EX_2_1_UCHAR);
    printf(">> Signed Char Max:\t%d\n", EX_2_1_CHAR_MAX);
    printf(">> Signed Char Min:\t%d\n\n", EX_2_1_CHAR_MIN);

    printf(">> Unsigned Short:\t%u\n", EX_2_1_USHORT);
    printf(">> Signed Short Max:\t%d\n", EX_2_1_SHORT_MAX);
    printf(">> Signed Short Min:\t%d\n\n", EX_2_1_SHORT_MIN);

    printf(">> Unsigned Int:\t%u\n", EX_2_1_UINT);
    printf(">> Signed Int Max:\t%d\n", EX_2_1_INT_MAX);
    printf(">> Signed Int Min:\t%d\n\n", EX_2_1_INT_MIN);

    printf(">> Unsigned Long:\t%lu\n", EX_2_1_ULONG);
    printf(">> Signed Long Max:\t%ld\n", EX_2_1_LONG_MAX);
    printf(">> Signed Long Min:\t%ld\n", EX_2_1_LONG_MIN);

    printf("%ld byte\n", ex_2_1_sizeof("char"));
    printf("%ld bytes\n", ex_2_1_sizeof("short"));
    printf("%ld bytes\n", ex_2_1_sizeof("int"));
    printf("%ld bytes\n", ex_2_1_sizeof("long"));

    return EXIT_SUCCESS;
}