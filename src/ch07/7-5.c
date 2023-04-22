/**
 * @file 7-5.c 改写第4章中的后缀计算器程序，用 scanf 函数 或者 sscanf 函数 实现输入及数的转换
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * command
1 2 - 4 5 + *
    2 3 4 + *   
0.456721 10 * 0.822135 9 * 0.080252 7 * 0 0.640293 - 2 * 0 0.792799 - 4 * + + + + 10 9 7 2 4 + + + + /
3.1415926
-8
-2.41 3.35 + -.79 .64 - /
1 0 /
1 2 &
abc
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXOP 100 /* 运算器或操作数的最大长度 */
#define MAXVAL 100 /* 栈的最大深度 */

void push(double f);
double pop(void);
int getop(double *op);

int sp = 0; /* 栈的下一个空闲位置 */
double val[MAXVAL]; /* 值栈 */

/* 逆波兰计算器 */
int main() {
    int type;
    double op, op2;

    while ((type = getop(&op)) != EOF) {
        switch (type) {
            case NUMBER:
                push(op);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %c\n", type);
                break;
        }
    }
    return 0;
}

/* getop: 获取下一个运算符或操作数 */
int getop(double *op) {
    int c;

    while((c = getchar()) == ' ' || c == '\t')
        ;
    if(!isdigit(c) && c != '.')
        return c; /* 不是数字 */
    ungetc(c, stdin);
    scanf("%lf", op); // 这里是 字母 l 不是 数字 1  
    return NUMBER;
}

/* push: 把f压入到值栈中 */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else 
        printf("error: stack full, cant't push %g", f);
}

/* pop: 弹出并返回栈顶的值 */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}


