#include <stdio.h>

/* 在不使用运算符&&或||的条件下编写一个上面的for循环语句等价的循环语句
    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
 */
#define MAXLINE 100
int main()
{
    int i = 0;
    int c;
    char s[MAXLINE]; // 定义一个用于存储字符串的字符数组
    int limit = MAXLINE;
    while (i < limit - 1)
    {
        /* code */
        if ((c = getchar()) == '\n') {
            break;
        } else if (c == EOF) {
            break;
        } else {
            s[i] = c;
            ++i;
        }
    }
    return 0;
}