#include <ctype.h>
#include <stdio.h>
/* 
    重新编写将字符串转换为对应数字的函数atoi
 */
int atoi(char s[]);
int main()
{
    int s = atoi("+432-4avb");
    printf("%d\n", s);
    return 0;
}

int atoi(char s[]) {
    int i, n, sign;
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') /* 跳过符号 */
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}