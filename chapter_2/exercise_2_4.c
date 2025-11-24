#include <stdio.h>
#include <stdbool.h>

void squeeze(char *s1, char *s2) {

    char in_s2 = false;
    int k = 0;
    
    for (int i = 0; s1[i] != '\0'; i++) {

        for (int j = 0; s2[j] != '\0'; j++) {

            if (s1[i] == s2[j]) {

                in_s2 = true;
                break;
            }
        }
        if (! in_s2 )
            s1[k++] = s1[i];

        in_s2 = false;
    }

    s1[k] = '\0';
}

int main() {

    char s1[1024] = {0};
    char s2[1024] = {0};

    printf("Insert a string: ");
    fgets(s1, sizeof(s1), stdin);
    
    printf("Chars to ignore: ");
    fgets(s2, sizeof(s2), stdin);
    
    squeeze(s1, s2);
    printf(">> \"%s\"", s1);
}