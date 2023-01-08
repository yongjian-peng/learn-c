/**
 * @file 4-9.c 以上介绍的getch与ungetch函数不能正确的处理压回的EOF，考虑压回EOF时应该
 * 如果处理？请实现你的方案
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
int getch(char s[], int p);
void ungetch(int c);
void ungets(char s[]);

#define BUFSIZE 100
int buf[BUFSIZE];

int bufp = 0;

int getch(char s[], int p)
{
    return (p > 0) ? s[--p] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        ungetch(s[i]);
    }
}

void print1(int arr[], int sz) // 通过数组接受的方式
{
    int i = 0;
    for (i = 0; i < sz; i++)
    {
        // printf("%d ", arr[i]);
        printf("%c ", arr[i]);
    }
    printf("\n");
}

int main()
{
    char *s = "hello world! \t";
    char *s2 = "A test for ungets!";

    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        ungetch(s[i]);
    }
    ungets(s2);

    int sz = sizeof(buf) / sizeof(buf[0]); // 计算数组元素个数

    print1(buf, sz);
    return 0;
}