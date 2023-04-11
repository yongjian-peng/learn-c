#include <stdio.h>

/* 实现库函数 strncpy strncat 和 strncmp 它们最多对参数字符串中的前n个字符进行操作，例如：函数strncpy(s, t, n) 将t 中最多前n个字符赋值到s中 */
/* 把字符串t中的前n个字符串拷贝到s中，如果t的字符数小于n，则拷贝到\0为止 */
void strncpy2(char *s, char *t, int n);
/* 实现将字符串t中最多n个字符连接到字符串s的尾部，并返回s */
void strncat2(char *s, char *t, int n);
/* 实现是将字符串s中最多前n个字符与字符串t相比较，当s<t时，返回一个负数，当s>t时返回一个正数 */
int strncmp2(char *s, char *t, int n);

void strncpy2(char *s, char *t, int n)
{
    while(*t && n-- > 0)
        *s++ = *t++;
    while(n-- > 0)
        *s++ = '\0';
}

void strncat2(char *s, char *t, int n)
{
    // void strncpy2()
}

int strncmp2(char *s, char *t, int n)
{
    for (; *s == *t; s++, t++)
        if(*s == '\0' || --n <= 0)
            return 0;
    return *s - *t;
}

int main() {
    char s[] = "abcdef3";
    char t[] = "ABCDEF";

    strncpy2(s, t, 4);

    printf("%s\n", s);

    printf("%d", strncmp2(s, t, 5));

    return 0;
}

