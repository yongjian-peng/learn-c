/**
 * @file 7-4.c 类似于上一节中的函数 minprintf 编写 scanf 函数的一个简化版本
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
a = -273, b=0x270f, c = 4294967295
430963776 = 03153776100 = 0x19AFFC40
pi = 3.1415926, N_A = 6.02e23, e = 1.60e-19
@
    hello, world!    
+15%
25 Dec 1988
2022-7-19
 * 
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

int minscanf(char *fmt, ...);

int main() {
    // double sum, v;

    // sum = 0;
    // while(scanf("%1f", &v) == 1)
    //     printf("\t%.2f\n", sum += v);
    int a, b, c;
    unsigned u;
    float x, y, z;
    char p, q;
    char s[20], t[20];

    // assert(minscanf("a = %d, b = %i. c = %u", &a, &b, &u) == 2);
    // assert(a == -273 && b == 0x270f);
    // assert(minscanf(" c = %u", &u) == 1);
    // assert(u == 4294967295u);

    // assert(minscanf("%d = %o = %x", &a, &b, &c) == 3);
    // assert(a == 430963776 && b == 430963776 && c == 430963776);

    // /* 注意在格式字符串开头加空格以读掉上一行的换行符 */
    // assert(minscanf(" pi = %f, N_A = %e, e = %g", &x, &y, &z) == 3);
    // assert(fabs(1 - x / 3.1415926) < 1e-6 && fabs(1 - y / 6.02e23) < 1e-6 && fabs(1 - z / 1.60e-19) < 1e-6);

    // assert(minscanf("%c%c", &p, &q) == 2);
    // assert(p == '\n' && q == '@');

    // assert(minscanf("%s%s", s, t) == 2);
    // assert(strcmp(s, "hello,") == 0 && strcmp(t, "world!") == 0);

    // assert(minscanf("%d%%", &a) == 1);
    // assert(a == 15);

    assert(minscanf("%d %s %d", &a, s, &b) == 3);
    assert(a == 25 && strcmp(s, "Dec") == 0 && b == 1988);

    assert(minscanf("%d-%d-%d", &a, &b, &c) == 3);
    assert(a == 2022 && b == 7 && c == 19);

    return 0;
}

/* minscanf: 带有可变参数表的简化的scanf */
int minscanf(char *fmt, ...) {
    va_list ap;
    int matched = 0;
    char format[] = "%d";
    char *p, c;
    void *pval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (isspace(*p)) {
            while(isspace(c = getchar()))
                ;
            ungetc(c, stdin);
            continue;
        }
        else if (*p != '%') {
            if (getchar() != *p)
                goto end;
            continue;
        }
        switch(*++p) {
            case '%':
                if (getchar() != '%')
                    goto end;
                break;
            default:
                pval = va_arg(ap, void *);
                format[1] = *p;
                if (!scanf(format, pval))
                    goto end;
                ++matched;
                break;
        }
    }
end:
    va_end(ap);
    return matched;
}