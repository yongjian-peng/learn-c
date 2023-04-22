/**
 * @file 7-1.c 根据被调用的名字将输入转换为小写或者大写的形式
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    char *sep, *name;
    enum {nothing, lower, upper} op = nothing;
    int c;

    sep = strrchr(argv[0], '/');
    name = sep ? sep + 1 : argv[0];

    if (strcmp(name, "tolower.out") == 0 || strcmp(name, "tolower") == 0)
        op = lower;
    else if (strcmp(name, "toupper.out") == 0 || strcmp(name, "toupper") == 0)
        op = upper;
    while((c = getchar()) != EOF)
        if (op == lower)
            putchar(tolower(c));
        else if (op == upper)
            putchar(toupper(c));
        else   
            putchar(c);
    return 0;
}