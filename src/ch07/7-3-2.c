/**
 * @file 7-3-2.c 改写minprintf 函数 使它能完成printf函数的更多功能
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main() {
    int ival = 42;
    unsigned uval = 0xdeadbeefU;
    char cval = '@';
    double dval = -1.234567e89;
    double dval2 = -12;
    char sval[] = "My name is Peter";
    void *pval = (void *) 0x9f36fae0;

    minprintf("%%d: %d\n", ival);
    minprintf("%%i: %i\n", ival);
    minprintf("%%u: %u\n", uval);
    minprintf("%%o: %o\n", uval);
    minprintf("%%x: %x\n", uval);
    minprintf("%%X: %X\n", uval);
    minprintf("%%c: %c\n", cval);
    minprintf("%%f: %f\n", dval);
    minprintf("%%e: %e\n", dval);
    minprintf("%%E: %E\n", dval);
    minprintf("%%g: %g\n", dval);
    minprintf("%%G: %G\n", dval);
    minprintf("%%g: %g\n", dval2); // 把输出的值按照%e或者%f 类型中输出长度较小的方式输出
    minprintf("%%G: %G\n", dval2);
    minprintf("%%s: %s\n", sval);
    minprintf("%%p: %p\n", pval);
    minprintf("%%%%: %%\n");
    minprintf("unchanged: %6d %1f\n", ival, dval);
    return 0;
}

/* minprint: 带有可变参数表的简化的printf */
void minprintf(char *fmt, ...) {
    va_list ap; /* 依次指向每个无名参数 */
    char format[] = "%d";
    char *p, *sval;
    int ival;
    unsigned uval;
    double dval;
    void *pval;

    va_start(ap, fmt); /* 将ap 指向第一个无名参数 */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch(*++p) {
            case 'd': case 'i': case 'c':
                ival = va_arg(ap, int);
                format[1] = *p;
                printf(format, ival);
                break;
            case 'u': case 'o': case 'x': case 'X':
                uval = va_arg(ap, unsigned);
                format[1] = *p;
                printf(format, uval);
                break;
            case 'f': case 'e': case 'E': case 'g': case 'G':
                dval = va_arg(ap, double);
                format[1] = *p;
                printf(format, dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                printf("%s", sval);
                break;
            case 'p':
                pval = va_arg(ap, void *);
                printf("%p", pval);
                break;
            case '%':
                putchar('%');
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); /* 结束时的清理工作 */
}
