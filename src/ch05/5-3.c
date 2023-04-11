#include <stdio.h>

/* 用指针的方式实现第二章中的函数 strcat 函数 strcat(s, t) 将t指向的字符串赋值到s指向的字符串的尾部 */

void strcat1(char *s, char *t);

int main() {
    char s[10] = "jyj";
    char t[] = "girl";
    strcat1(s, t);
    printf("%s ", s);
    return 0;
}

void strcat1(char *s, char *t)
{
    while(*s != '\0')
        s++;
    while (*t != '\0')
    {
        /* code */
        *s = *t;
        t++;
        s++;
    }
    *s = '\0';    
}