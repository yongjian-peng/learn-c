/*
    给计算器程序增加处理变量的命令
    （提供26个具有英文字母变量名的变量很容易）。
    增加一个变量存放最近打印的值。
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

int main()
{
    int i, type, var = 0;
    double op2, v;
    char s[MAXOP];
    double variable[26];

    for (i = 0; i < 26; i++)
        variable[i] = 0;
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if(op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '=':
            pop();
            if(var >= 'A' && var <= 'Z')
                variable[var - 'A'] = pop();
            else
                printf("error: no varble name \n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            if (type >= 'A' && type <= 'Z')
                push(variable[type - 'A']);
            else if (type == 'v')
                push(v);
            else
                printf("error: unknow command %s\n", s);
            break;
        }
        var = type;
    }

    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

// push 操作 把值压入堆栈
void push(double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    }
    else
    {
        printf("error: stack full, can't push %g\n", f);
    }
}

// pop 操作 从堆栈中弹出值
double pop(void)
{
    if (sp > 0)
    {
        return val[--sp];
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>
int getch(void);
void ungetch(int);

// getop 获取下一个操作数或运算符
int getop(char s[])
{
    int i, c;
    // 跳过空格制表符
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    // 不是数字，返回
    if (!(isdigit(c)) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-')
    {
        if (isdigit(c = getch()) || c == '.')
        {
            s[++i] = c;
        }
        else
        {
            if (c != EOF)
            {
                ungetch(c);
            }
            return '-';
        }
    }
    // 收集正数部分
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    // 收集小数部分
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
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
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// 把要压回的字符串放到缓冲区
void ungetch(int c)
{
    if (bufp > BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
        buf[bufp++] = c;
}