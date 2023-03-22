#include <stdio.h>

// int a[5]; // 放在不同的地方 得出的结果是不同的 
// 参考 https://blog.csdn.net/weixin_55697693/article/details/127835873
int main() {
    int a[5];
    int i;
    for (i = 0; i < 100; i++)
        a[i] = i + 1;
    for (i = 0; i < 100; i++)
        printf("arr i, %d,: %d ", i, a[i]);

    printf("%d %d", &a[0], &a[200]);
    return 0;
}