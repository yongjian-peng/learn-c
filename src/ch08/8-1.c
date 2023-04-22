/**
 * @file 8-1.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>

int getchar(void);

int main() {
    // char buf[BUFSIZ];
    // int n;

    // while((n = read(0, buf, BUFSIZ)) > 0)
    //     write(1, buf, n);

    // int c = getchar();
    // printf("%d\n", c);

    int a = getchar2();
    printf("%d\n", a);

    return 0;
}

int getchar(void) {
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

int getchar2(void) {
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    if (n == 0) {
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}