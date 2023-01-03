#include <stdio.h>
#include <string.h>
/* 
    重新编写函数squeeze(s1, s2),将字符串s1中任何与字符串s2中
    字符串匹配的字符都删除
 */
#define SIZE 0xff

void squeeze(char s1[], char s2[]);

int main() {
    char s1[] = "bcdefabcghi";
    char s2[] = "aaabc";

    squeeze(s1, s2);
    printf("%s\n", s1);
    printf("%s\n", s2);
    return 0;
}

void squeeze(char s1[], char s2[]) {
    printf("%d\n", SIZE);
    char symbol[SIZE] = {};
    int i, j;

    for (i = 0; s2[i] != '\0'; ++i){
        // 标记存在
        symbol[s2[i]] = 1;
    }

    i = j = 0;

    while(s1[i] != '\0') {
        // s1[i] = '\0';
        // 存在的话 则记录i++
        while (symbol[s1[i]]) {
            // printf("- %d ", i);
            i++;
        }
        // printf("+ %d ", i);
        printf(" %d ", j);
        // printf("k %c", s1[j++]);
        s1[j++] = s1[i++];
        // i++;
    }
    printf("+ %d", j);
    printf(" %c ", s1[j]);
    s1[j] = '\0';
}
