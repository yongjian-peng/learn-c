#include <stdio.h>
/* 
    编写函数any(s1, s2),将字符串s2中的任一字符在字符串s1中第一次出现的位置
    作为结果返回，如果s1中不包含s2中的字符，则返回-1，
    （标准库函数strpbrk具有相同的功能，但它返回的是指向该位置的指针）
 */
int indexof(char s[], char c);
int any(char s1[], char s2[]);
int main()
{
    printf("any(\"hello fool2fish!\", \"f2f\") -> %d\n", any("hello fool2fish", "f2f"));
    printf("any(\"hello fool2fish!\", \"yzx\") -> %d\n", any("hello fool2fish", "yzx"));
}

int indexof(char s[], char c) {
    int i = 0;
    char ch;
    while((ch = s[i++]) != '\0') {
        if (ch == c) {
            return --i;
        }
    }
    return -1;
}

int any(char s1[], char s2[]) {
    int i = 0;
    char c;
    while((c = s1[i++]) != '\0') {
        int idx = indexof(s2, c);
        if (idx != -1) {
            return --i;
        }
    }
    return -1;
}