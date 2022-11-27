#include <stdio.h>
#include <ctype.h>
/* 编写一个程序，以每行一个单词的形式打印其输出 */
int main() {
    int isIn = 0;
    char c;

    while((c = getchar()) != EOF) {
        if (isIn) {
            if (isspace(c)) {
                isIn = 0;
                putchar('\n');
            } else {
                putchar(c);
            }
        } else {
            if (!isspace(c)) {
                isIn = 1;
                putchar(c);
            }
        }
    }
    return 0;
}