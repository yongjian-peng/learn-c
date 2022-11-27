#include <stdio.h>

/* 编写一个删除C语言程序中所有的注释语句。要正确处理带引号的字符串与字符常量，在C语言中，注释不允许嵌套
 */

int main()
{
    char prevc;
    char c;
    char nextc;
    while((c = getchar()) != EOF) {
        if (c == '"') {
            putchar(prevc = c); // 打印开始双引号
            while ((c = getchar()) != '"' || prevc == '\\') {
                putchar(prevc = c);
            }
            putchar(prevc = c); // 打印结束双引号
        }else if (c == '/') {
            nextc = getchar();
            if (nextc == '/') {
                while ((c = getchar()) != '\n')
                    ;
                putchar('\n');
            } else if (nextc == '*') {
                prevc = getchar();
                while((c = getchar()) != '/' || prevc != '*') {
                    prevc = c;
                }
            } else {
                putchar(c);
                putchar(prevc = nextc);
            }
        }else {
            putchar(prevc = c);
        }
    }
    return 0;
}
