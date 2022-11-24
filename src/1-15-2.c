#include <stdio.h>

/* 字符数组 记录最长字符 */
#define MAXLINE 1000 /* 允许的输入的最大长度 */
int getline1(char line[], int maxline);
void copy(char to[], char from[]);
int main()
{
    int len; /* 当前行长度 */
    int max; /* 目前为止发现的最长的长度 */
    char line[MAXLINE]; /* 当前的输入行 */
    char longest[MAXLINE]; /* 用于保存最长的字符 */

    max = 0;
    while((len = getline1(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)
        printf("%s", longest);
    return 0;
}

int getline1(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\n';
    return i;
}

void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\n')
        ++i;
}
