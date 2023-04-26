#include <stdio.h>

void enter_string(char str[]) {
    printf("Input a string");
    fgets(str, 50, stdin);
}