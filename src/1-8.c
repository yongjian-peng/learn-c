#include <stdio.h>
/* 
    编写一个统计空格 制表符与换行符个数的程序
 */
int space = 0;
int tab = 0;
int newline = 0;

int main() {
    int c;
    while((c = getchar()) != EOF) {
        switch (c)
        {
        case ' ':
            /* code */
            space++;
            break;
        case '\t':
            tab++;
            break;
        case '\n':
            newline++;
            break;
        default:
            break;
        }
    }
    printf("space:%d, tab:%d, newline:%d\n", space, tab, newline);
    return 0;
}