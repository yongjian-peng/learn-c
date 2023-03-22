#include <stdio.h>
#include <string.h>
/* 编写函数 strend(s,t) 如果字符串 t 出现再字符串s 的尾部，该函数返回 1 否则返回 0 */

int strend2(char *s, char *t);

int strend2(char *s, char *t) {
    while (*s != *t)
    {
        if (*s == '\0')
            return 0;
        s++;
    }
    while(*s == *t) {
        if (*s == '\0')
        {
            return 1;
        }
        s++;
        t++;
    }
    return 0;
}

int main() {
    char a[] = "hello,world!";
    char t[] = "world!";
    printf("%d", strend2(a, t));
    return 0;
}