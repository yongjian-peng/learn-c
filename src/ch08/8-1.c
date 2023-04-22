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

    int b = 5;
    // printf("%s\n", b);
    b |= 3; // b 现在的值为7 即二进制 0111 | 代表位或操作符 而 = 代表 赋值操作符 |= 是一种组合操作符
        // 它将按位或结果赋值给左侧的操作数， 5
        // 5 0101
        // 3 0011
        // 7 0111
    printf("%d\n", b);

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