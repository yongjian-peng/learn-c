/**
 * @file 7-3.c minprintf 初级实现
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main() {
    minprintf("a = %d\n", 42);
    minprintf("pi = %f\n", 3.1415926);
    minprintf("My name is %s.\n", "Peter");
    minprintf("unchanged: %c %6d %u %1f %p %%\n", 'x', 123, -1, 1e50, &minprintf);

    int ar2[3][2];
    int **p2;
    p2 = ar2[0];


    return 0;
}


/* minprintf: 带有可变参数表的简化的printf */
void minprintf(char *fmt, ...) {
    va_list ap; /* 依次指向每个无名参数 */
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt); /* 将ap指向第一个无名参数 */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p)
        {
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap); /* 结束时的清理工作 */
}