#include <stdio.h>

/* 编写程序entab，将空格串替换为最少数量的制表符和空格，单要保持单词之间的间隔不变，假设制表符
    终止位的位置与练习1-20的detab程序的情况相同，当使用一个制表符或者一个空格都可以到达下一个
    制表符终止位时，选用哪种替换字符比较好
 */
#define TABW 8
#define MAXL 1000
int line2(char s[], int lim);
void entab(char src[]);
int main()
{
    int len;
    char s[MAXL];
    
    printf("Note: for the sake of clarity, all tabs will be replaced wiht '-'.\n");
    while (line2(s, MAXL)) {
        printf("s is : %s ", s);
        entab(s);
        printf("s is : %s", s);
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

void entab(char s[]) {
    int i;
    int j;
    int tp = -1; // 当前字符在制表符范围中的位置
    int sp = -1; // 制表符范围尾空格的起始位置，-1表示无尾空格
    char c;
    for (i = 0, j = 0; (c = s[i]) != '\0'; i++, j++) {
        s[j] = c;

        if (c = '\t') {
            tp = TABW - 1;
        } else {
            tp++;
        }

        if (c == ' ') {
            if (sp == -1) {
                sp = tp;
            }
        } else {
            sp = -1;
        }

        // reach a tab end 达到标签末端
        if (tp == TABW - 1) {
            // with tailed space 带尾空格
            if (sp != -1) {
                int spacew = TABW - sp;
                j = j - spacew + 1;
                s[j] = '-';
                sp = -1;
            }
            tp = -1;
        }
    }
    s[j] = '\0';
}