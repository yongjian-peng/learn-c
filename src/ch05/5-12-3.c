#include <stdio.h>
#include <string.h>

int main() {

    int i = 10;
    printf("i value is: %d\n", &i);

    printf("i address is: %p\n", &i);

    int *pp = 0;

    pp = &i;

    printf("pp value: %d\n",pp);
    printf("pp addr is : %p\n", pp);
    printf("pp x value: %x\n", *pp);
    printf("pp d value: %d\n", *pp);

    int m = 5;
    int n = 10;

    printf("%d%d\n", m, m + n);

    return i;
}