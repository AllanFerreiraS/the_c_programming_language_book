/*
 *Write a program entab that replaces strings of blanks by the minimum number 
 *of tabs and blanks to achieve the same spacing. 
 *Use the same tab stops as for detab. 
 *When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
 * */

#include <stdio.h>
#define TAB_COLLUM      8
#define MAXLINE         1000

int main() {
    
    int c, i, a, count, tab_next_stop;
    char input[MAXLINE];

    i = a = count = tab_next_stop = 0;

    for (int j = 0; j < MAXLINE; j++)
        input[j] = '\0';
    
    while(a < MAXLINE - 2 && (c = getchar()) != '\n') {
        if (c == ' ') {
            tab_next_stop = TAB_COLLUM - (i % TAB_COLLUM);
            if (tab_next_stop <= 1) {
                input[a] = '\t';
                ++a;
                count = 0;
            }
            else {
                ++count;
            }
        }
        else {
            if (count > 0) {
                for (; count > 0; --count) {
                    if (a < MAXLINE - 2) {
                        input[a] = ' ';
                        ++a;
                    }
                }
            }
            if (a < MAXLINE - 2) {
                input[a] = c;
                ++a;
            }
        }
        ++i;
    }

    input[a] = '\n';
    
    if (i > 0)
        printf("%s", input);

    return 0;    
}

