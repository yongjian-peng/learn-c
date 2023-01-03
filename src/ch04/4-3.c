/**
  逆波兰表达式
  输入 1 2 - 4 5 + *   -9
  1 2 + 3 4 + *    21
  在计算器中加入取模%操作， 注意考虑负数的情况
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != 'EOF') {
        switch (type)
        {
            // 是数则压入栈
        case NUMBER:
            push(atof(s));
            break;
        // 是操作符则取出操作需要数目的数，运算后将结果入栈
        case '+':
            push(pop()+pop());
            break;
        case '-':
            op2 = pop();
            push(pop()-op2);
            break;
        case '*':
            push(pop()*pop());
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop()/op2);
            else 
                printf("error: zero divisor.\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else 
                printf("error: zero divisor.\n");
            break;
        case '\n':
            printf("计算结果：%.8g\n", pop());
            break;
        default:
        printf("error: unknown command.\n");
            break;
        }
    }
    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

// push 操作 把值压入堆栈
void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

// pop 操作 从堆栈中弹出值
double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>
int getch(void);
void ungetch(int);

// getop 获取下一个操作数或运算符
int getop(char s[]) {
    int i, c;
    // 跳过空格制表符
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // 不是数字，返回
    if (!(isdigit(c)) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-') {
        if (isdigit(c = getch()) || c == '.') {
            s[++i] = c;
        } else {
            if (c != EOF) {
                ungetch(c);
            }
            return '-';
        }
    }
    // 收集正数部分
    if (isdigit(c))
        while(isdigit(s[++i]= c = getch()))
            ;
    // 收集小数部分
    if (c == '.')   
        while(isdigit(s[++i] = c = getch())) 
            ;
    s[i] = '\0';
    if (c != EOF)
    {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZ];
int bufp = 0;

// 缓冲区不为空则getch从缓冲区读出字符，否则用 getchar 函数直接从输入读取
int getch(void) {
    return (bufp > 0) ? buf[--bufp]: getchar();
}

// 把要压回的字符串放到缓冲区
void ungetch(int c) {
    if (bufp > BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else 
        buf[bufp++] = c;
}