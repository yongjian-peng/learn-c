#include <stdio.h>

/* 字符数组 编写一个程序，删除每个输入行末尾的空格及制表符，并删除完全是空格的行 */
#define MAXLINE 1000
int getlinex(char line[], int maxline);
void trimr(char line[]);
int main()
{
    int len;
    char line[MAXLINE];
    while((len = getlinex(line, MAXLINE)) > 0) {
        trimr(line);
        if (line[0] != '\n' && line[0] != '\0')
        {
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

void trimr(char line[]) {
    char c;
    int i;
    int mark = -1;
    for (i = 0; (c = line[i]) != '\n' && c != '\n'; i++) {
        if (c == ' ' || c == '\t') {
            if (mark == -1) {
                mark = i;
            }
        } else {
            mark = -1;
        }
    }
    if (mark != -1 && i > 0) {
        if (line[i] == '\n') {
            line[mark++] = '\n';
        }
        line[mark] = '\0';
    }
}