#include <stdio.h>

/**
 * 段错误demo 
 */
int main(void) {
    printf("core.c\r\n");
    int *core = NULL;
    *core = 1;
    printf("%d\n", *core);
    return 0;
}