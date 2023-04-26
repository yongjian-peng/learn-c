/**
 * @file 7-2.c 编写一个程序，以合理的方式打印任何输入，该程序至少能够根据用户的习惯以八进制或者十六进制
 * 打印非图形字符，并截断长文本行
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100
int getline(char line[], int lim);

int main() {
    char s[] = "hello, world";
    printf(":%s:\n", s);
    printf(":%10s:\n", s);
    printf(":%.8s:\n", s);
    printf(":%-10s:\n", s);
    printf(":%.15s:\n", s);
    printf(":%15.10s:\n", s);
    printf(":%-15.10s:\n", s);

    char a = 'y';

    printf("\\x%02hhx\n", s[0]);
    printf("\\%02hhx", a);

    char line[MAXLINE];
    int len, i;
    while((len = getline(line, MAXLINE)) > 0)
        for (i = 0; i < len; ++i)
            if (isprint(line[i]))
                putchar(line[i]);
            else
                printf("\\x%02hhx", line[i]);

    return 0;
}

/* getline: 将一行读入到line中并返回其长度 */
int getline(char line[], int lim) {
    int c = EOF, i;
    i = 0;
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}