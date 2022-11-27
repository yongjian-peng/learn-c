#include <stdio.h>

/* 字符数组 打印最长的输入行，特别版本 */
#define MAXLINE 1000 /* 允许的输入行的最大长度 */
int max;             /* 到目前为止发现的最长行的长度 */
char line[MAXLINE];  /* 当前输入的行 */
char logest[MAXLINE]; /* 用于保存最长行 */
int getlinex(void);
void copy(void);
int main()
{
    int len;
    int max;
    extern char longest[];

    max = 0;
    while((len = getlinex()) > 0) {
        if (len > max) {
            max = len;
            copy();
        }
    }
    if (max > 0)
        printf("%5d: %s", len, logest);
    return 0;
}

int getlinex(void) {
    int c, i;
    extern char line[];
    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

void copy(void) {
    int i;
    extern char line[], logest[];
    i = 0;
    while((logest[i] = line[i]) != '\0')
        ++i;
}