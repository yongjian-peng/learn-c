#include <stdio.h>

/* 字符数组 修改打印最长文本的程序的主程序 main，使之可以打印任意长度的输入行的长度，并尽可能多地打印文本 */
#define MAXLINE 1000
int getlinex(char line[], int maxline);
int main()
{
    int len;
    char line[MAXLINE];
    while((len = getlinex(line, MAXLINE)) > 0) {
        printf("%5d: %s", len, line);
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