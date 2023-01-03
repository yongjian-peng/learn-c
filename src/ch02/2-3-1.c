#include <stdio.h>
#include <limits.h>
/* 字符变量都会被转换为整形变量
    当把较长的整数转换为较短的整数或char类型时，超出的高位部分将被丢弃
 */
int main() {
    int i = 130;
    char c = 'z';
    c = i;
    i = c;
    // c = i;
    printf("Unsigned int max %d\n", i);
    printf("Unsigned int max %d\n", c);
    return 0;
}