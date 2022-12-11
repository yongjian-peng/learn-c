#include <stdio.h>
/* 
    编写一个函数Invert(x,p,n), 该函数返回对x执行下列操作后的结果值，
    将x中的第p位开始的n个（二进制）位求反（即，1变成0,0变成1）
    x的其余各位保持不变
 */

int bitlen(unsigned d);
unsigned invert(unsigned x, unsigned p, unsigned n);

int main() {
    printf("invert(5, 1, 1) -> %u\n", invert(5, 1, 1));
    printf("invert(5, 4, 1) -> %u\n", invert(5, 4, 1));
}

int bitlen(unsigned d) {
    int len = 0;
    for (; d; d >>=1) {
        len++;
    }
    return len;
}

unsigned invert(unsigned x, unsigned p, unsigned n) {
    int len = bitlen(x);

    if (len < p + n) {
        printf("Error: illegal p <%u> or n<%u>.\n", p, n);
        return 0;
    } else {
        unsigned tail = len - p - n;
        unsigned right = x & ~(~0 << tail);
        x >>= tail;
        x ^= ~(~0 << n);
        x <<= tail;
        x |= right;
        return x;
    }
}