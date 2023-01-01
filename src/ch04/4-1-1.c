/*
    编写函数strrindx(s, t), 它返回字符串t在s中最右边出现的位置，如果
    s中不包含t，则返回-1.
*/
#include <stdio.h>
int strindex(char s[], char t[]);
int strindex2(char s[], char t[]);

int main() {
    char s[] = "hello 00000 hello 00000";
    char t[] = "hello";
    int index;

    index = strindex(s, t);
    printf("%d\n", index);

    index = strindex2(s, t);
    printf("%d\n", index);

    return 0;
}

int strindex(char s[], char t[]) {
    int i, j, k, l;
    // s的最右下标
    for (i = 0; s[i] != '\0'; i++)
        ;
    // t的最右下标
    for (j = 0; t[j] != '\0'; j++)
        ;
    j--; //  去掉 '\0'
    while(--i >= j) // 如果剩余的字符个数已经小于t的长度，那么就不用继续了
    {
        k = i;
        l = j;
        while(l >= 0 && s[k--] == t[l--])
            ;
        if (l < 0) // 如果全部匹配完成 l 应该是-1
            return ++k; // 因为是s[k--] 所有要把最后减掉的数加 1
    }
    return -1;
}
int strindex2(char s[], char t[]) {
    int i, j, k, l;
    l = -1;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (t[k] == '\0')
            l = i;
    }
    return l;
}