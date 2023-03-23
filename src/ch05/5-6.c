#include <stdio.h>

/* 采用指针的方式而非数组索引的方式改写前面章节和练习中的某些程序，例如getline(第1、4章)，atoi, itoa 以及他们的变体形式（第2,3,4章）reverse(第三章)，strindex getop （第四章） */

/* 对于书中的getop 函数和 atof函数的指针形式就是在原来的基础上 把类似于s[i++]形式改成*s++
 * 把s[++i] 改成 *++s 函数逻辑没有任何变化。
 * */

#define MAXLINE 1000 /* 最大输入行数 */

int getline1(char line[], int max);
int strindex(char *s, char *t);

char pattern[] = "ould"; /* 待查找的模式 */

/*找出所有与模式匹配的行*/
int main() {
    char line[MAXLINE];
    int found = 0;
    int lineNu;

    while(getline1(line, MAXLINE) > 0) {
        lineNu = strindex(line, pattern);
        if (lineNu >= 0) {
            printf("%s", line);
            found++;
        }
        printf("lineNu: %d\n", lineNu);
    }
        
    printf("%d\n", found);
    return found;
}

/* getline 函数 将行保存到s中，并返回改行的长度 */
int getline1(char s[], int lim) {
    int c, i;
    i = 0;
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* strindex函数，返回t在s中的位置，若未找到则返回-1 */
// int strindex(char s[], char t[]) {
//     int i, j, k;
//     for (i = 0; s[i] != '\0'; i++) {
//         for (j = 1, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
//             ;
//         if (k > 0 && t[k] == '\0')
//             return i;
//     }
//     return -1;
// }

/* strindex函数，返回t在s中的位置，若未找到则返回-1 */
int strindex(char *s, char *t) {
    char *bs = s;
    char *bt = t;
    int i;
    for(i = 0; *s != '\0'; s++, i++)
    {
        for(bs = s, bt = t; *bt != '\0' && *bs == *bt; bs++, bt++)
            ;
        if (*t != '\0' && *bt == '\0')
            return i;
    }
    return -1;
}
