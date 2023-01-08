/**
 * @file 4-7.c 编写一个函数 ungets(s) 将整个字符串s压回到输入中，ungets函数需要使用
 * buf和bufp吗，它能否仅使用ungetch函数吗
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
char buf[BUFSIZE];

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

int main()
{
    char *s = "hello world!";
    char *s2 = "A test for ungets!";

    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        ungetch(s[i]);
    }
    ungets(s2);

    printf("%s\n", buf);
    return 0;
}