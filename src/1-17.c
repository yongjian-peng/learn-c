#include <stdio.h>

/* 字符数组 编写一个程序，打印长度大于80个字符的所有输出 */
#define MAXLINE 1000
int getlinex(char line[], int maxline);
int main()
{
    int len;
    char line[MAXLINE];
    while((len = getlinex(line, MAXLINE)) > 0) {
        if (len > 8) {
            printf("%5d: %s", len, line);
        }
    }
    return 0;
}

int getlinex(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}