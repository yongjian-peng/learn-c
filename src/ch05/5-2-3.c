#include <stdio.h>

int main() {
    unsigned int x = 4294967295; // 2^32 - 1
    x = x + 1; // x 现在为 0
    printf("%d\n", x);

    int y = 2147483647; // 2^31 - 1
    y = y + 1; // x 现在为 -2147483648
    printf("%d\n", y);

    int h = 32767; // 2^15 - 1
    int i = 32767; // 2^15 - 1
    int g = h * i; // g 现在为 -32769
    printf("%d\n", g);

    int o = -2147483648; // -2^31
    int p = -100;
    int q = o / p; // z 的值未定义
    printf("%d\n", g);


    return 0;
}