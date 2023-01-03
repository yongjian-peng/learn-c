#include <stdio.h>

/* 编写函数reverse(s), 将字符串s中的字符顺序颠倒过来，使用该函数编写一个程序，每次颠倒一个输入行中的字符顺序 */
#define MAXLEN 1000
int line1(char s[], int maxlen);
void reverse(char s[]);
int main()
{
    char s[MAXLEN + 1];
    while(line1(s, MAXLEN)) {
        reverse(s);
        printf("%s", s);
    }
    return 0;
}
int line1(char s[], int maxlen) {
    char c;
    int i;
    for (i = 0; (c = getchar()) != EOF && i < maxlen - 1; i++) {
        s[i] = c;
        if (c == '\n')
            break;
    }
    s[i] = '\0';
    return i;
}

void reverse(char s[]) {
    int len = 0;
    for (len = 0; s[len] != '\0'; len++)
        ;
    // 获取 字符串的长度
    if (len > 0 && (s[len - 1] == '\n')) {
        len--;
    }

    char temp;
    int i;
    for (i = 0; i < len / 2; i++)
    {
        int j = len - 1 - i;
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}