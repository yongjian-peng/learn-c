#include <stdio.h>
/* 
    在求对二的补码时，表达式x&=(x-1)可以删除x中最右边的值为1的一个二进制位。
    请解释这样做的道理。用这一方法重写bigcount函数，以及加快其执行速度
 */
int bitcount(unsigned x);
int main()
{
    printf("%d's, bit count is: %d\n", 1023, bitcount(1023));
    printf("%d's, bit count is: %d\n", 1024, bitcount(1024));
}

int bitcount(unsigned  x) {
    int len = 0;
    for (; x; x &= x - 1) {
        len++;
    }
    return len;
}