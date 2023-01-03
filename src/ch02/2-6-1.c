#include <stdio.h>
unsigned getbits(unsigned x, int p, int n);
/*  */
int main() {
    printf("%d\n", getbits(123320, 2, 3));

    int un;
    int un2;
    int un3;
    int un4;
    int un5;
    int un6;
    int up7;
    un = ~0;
    printf("un ~0: %d\n", un);

    un2 = ~0 << 3; // -1

    printf("un2 ~0 << 3: %d\n", un2); // 8

    un3 = ~(~0 << 3);
    printf("un3 ~(~0 << 3): %d\n", un3); // 7

    un4 = 10 >> 1;
    printf("un4 10 >> 1: %d\n", un4);

    un5 = un4 & un3;

    printf("un4 & un3: %d\n", un5);

    int i = 47;
    printf("%x\n", i);
    printf("%X\n", i);
    printf("%#x\n", i);
    printf("%#X\n", i);

    return 0;
}

unsigned getbits(unsigned x, int p, int n) {
    return (x >> (p + 1 - n)) & ~(~0 << n);
}