/**
 * @file 7-9.c 类似于 isupper 这样的函数可以通过某种方式实现以达到节省空间或时间的目的
 * 考虑节省空间或时间的方式
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>

int isupper(int c);

int main() {
    char a = 'B';
    printf("%d\n", isupper2(a));

    return 0;
}

int isupper(int c) {
    return (c >= 'A' && c <= 'Z');
}

int isupper2(int c) {
    return (strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", c) != NULL);
}

// int isupper3(int c) {
//     return ((_Ctype[(unsigned char)c] & _UP) != 0);
// }
