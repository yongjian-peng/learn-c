#include <stdio.h>

/* 编写程序detab，将输入中的制表符替换成适当数据的空格，使空格充满到下一个制表符终止的地方
    假设制表符终止位置是固定的，比如每隔n列就会出现衣蛾制表符终止符，n应该作为变量还是常量符号呢？
 */
#define TABW 8
#define MAXL 1000
int line2(char s[], int lim);
void detab(char src[], char tar[]);
int main()
{
    int len;
    char s[MAXL];
    char t[MAXL * TABW];

    printf("Note: for the sake of clarity, all tabs will be replaced wiht '-'.\n");
    while (line2(s, MAXL)) {
        printf("s is : %s ", s);
        detab(s, t);
        detab(s, t);
        printf("t is: %s, s is : %s", t, s);
    }
    return 0;
}

int line2(char s[], int lim) {
    char c;
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n' && i < lim - 1) {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';
    return i;
}

void detab(char src[], char tar[]) {
    int i;
    int j = 0;
    int spacew;
    char c;
    for (i = 0; (c = src[i]) != '\0'; i++) {
        if (c != '\t') {
            tar[j++] = c;
        } else {
            spacew = TABW - j % TABW;
            while (spacew-- > 0) {
                tar[j++] = '-';
            }
        }
    }
    tar[j] = '\0';
}