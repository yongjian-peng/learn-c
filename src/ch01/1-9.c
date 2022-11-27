#include <stdio.h>

/*
    编写一个将输入复制到输出的程序， 并将其中连续的多个空格用一个空格代替
*/
int main() {
    // char prev;
    // char c;
    // while((c = getchar()) != EOF) {
    //     if (c != ' ' || prev != ' ') {
    //         putchar(prev = c);
    //     }
    // }

    char *s;
    int p = 0;
    char prev;
    char c;
    while((c = getchar()) != EOF) {
        if (c != ' ' || prev != ' ') {
            *(s + p++) = prev = c;
        }
    }
    printf("\n%s", s);
    return 0;
}