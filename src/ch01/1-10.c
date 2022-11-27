#include <stdio.h>

/*
    编写一个将输入复制到程序，并将其中的制表符替换为\t
    把回退符替换成\b
    把反斜杠替换成\\
    这样可以将制表符和回退符可见的方式显示出来
*/
int main() {
    char c;
    while((c = getchar()) != EOF) {
        if (c == '\t') {
            putchar('\\');
            putchar('t');
        } else if(c == '\b') {
            putchar('\\');
            putchar('b');
        } else if(c == '\\') {
            putchar('\\');
            putchar('\\');
        }else {
            putchar(c);
        }
    }
    return 0;
}