#include <stdio.h>
#include <limits.h>
/* 编写一个程序以确定分别由signed及unsigned限定的char short int 与 long
    类型变量的取值范围，采用打印标准头文件中的相应值以及直接计算两种方式实现
    后一种方法的实现较困难一些，因为要确定各种浮点类型的取值范围
 */
int main() {
    printf("Unsigned char max: %d\n", UCHAR_MAX);
    printf("Signed char max %d\n", SCHAR_MAX);
    printf("Signed char min %d\n", SCHAR_MIN);

    unsigned int i = ~0;

    printf("Unsigned int max %u\n", i);
    printf("Unsigned int max %d\n", i);
    printf("Signed int max %d\n", i / 2);
    printf("Signed int min %d\n", -(i / 2) - 1);
}