#include <stdio.h>

/* 
    编写一个函数rightrot(x, n), 该函数返回将x循环右移
    （即从最右端移出的位将从最左端移入）n
    (二进制)位后所得到的值。
 */
int bitlen(unsigned d);
unsigned rightrot(unsigned d, unsigned x);

int main()
{
    printf("rightrot(11, 1) -> %u\n", rightrot(11, 8));
    printf("rightrot(1024, 14) -> %u\n", rightrot(1024, 14));
}

int bitlen(unsigned d) {
    int len = 0;
    for (; d; d >>= 1) {
        len++;
    }
    return len;
}

unsigned rightrot(unsigned d, unsigned x) {
    int len = bitlen(d);
    if (len) {
        x %= len;
        if (x) {
            unsigned right = d & ~(~0 << x);
            return right << len - x ^ d >> x;
        } else {
            return d;
        }
    } else {
        return 0;
    }
}