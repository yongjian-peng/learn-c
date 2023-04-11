#include <stdio.h>
/**
 * @brief 修改 entab和detab 程序，使其能够处理制表符停靠的位置与给定的参数不同
 * 的情况，具体来说 我们实现两个函数
 * 1. entab_custom(int tag_stop): 将输入的空格序列替换为最少数量的制表符和空格字符
 * 以便将空格序列替换为制表符停靠位置不同的制表符序列，tab_stop 参数表示制表符每隔多少列出现一次
 * 2. detab_custom(int tab_stop)： 将输入的制表符替换为适当数量的空格，使得制表符停靠到给定的列位置，
 * tab_stop 参数表示制表符每隔多少列出现一次
 * 
 */

#define MAXLINE 1000
#define TABSTOP 8

int getline_custom(char line[], int maxline);
void entab_custom(int tab_stop);
void detab_custom(int tab_stop);

int main() {
    int len;
    char line[MAXLINE];

    while((len = getline_custom(line, MAXLINE)) > 0) {
        entab_custom(TABSTOP);
        printf("%s", line);
        detab_custom(TABSTOP);
        printf("%s", line);
    }
    return 0;
}

int getline_custom(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

/* entab_custom: replace blanks with minimum number of tabs and blanks */
void entab_custom(int tab_stop)
{
    int c, i, nb, nt, pos;
    int blanks = 0; /* number of consecutive blanks */

    for (i = 0, pos = 0, nb = 0, nt = 0; (c = getchar()) != EOF; ++i) {
        if (c == ' ') {
            ++blanks;
            if ((pos + blanks) % tab_stop == 0) { /* should insert tab */
                ++nt;
                blanks = 0;
            }
        } else {
            for (; nt > 0; --nt)
                putchar('\t');
            if (c == '\t')
                pos = pos + (tab_stop - (pos % tab_stop));
            else 
                ++pos;
            
            for (; blanks > 0; --blanks)
                putchar(' ');
            
            putchar(c);

            if (c == '\n')
                pos = 0;
            else if (c == '\t')
                pos = pos + (tab_stop - (pos % tab_stop));
            else 
                ++pos;
        }
    }
}

void detab_custom(int tab_stop)
{
    int c, i;
    for (i = 0; (c = getchar()) != EOF; ++i)
    {
        if (c == '\t') {
            do {
                putchar(' ');
                ++i;
            } while (i % tab_stop != 0);
        } else {
            putchar(c);
        }
    }
}

