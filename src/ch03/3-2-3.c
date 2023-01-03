#include <stdio.h>
#include <string.h>
/* 
    reverse(s)函数，用于倒置字符串s中各个字符的位置
 */
void reverse(char s[]);


int main()
{
    char ss[] = "abcdef";
    reverse(ss);
    printf("%s\n", ss);
    return 0;
}
/* reerse函数，倒置字符串s中各个字符的位置*/
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}