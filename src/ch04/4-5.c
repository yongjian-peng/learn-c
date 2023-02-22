/**
 逆波兰表达式 
 给计算器程序增加访问 sin exp 与 pow 等库函数操作 有关这些库函数
 的详细信息 参见附录B.4节中的头文件<math.h>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define NAME '1'

int getop(char []);
void push(double);
double pop(void);
void mathlib(char[]);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch(type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop()*pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else 
                    printf("error: zero divisor\n");
                break;
            case NAME:
                mathlib(s);
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknow command %s\n", s);
                break;
        }
    }
    return 0;    
}

void mathlib(char s[]) 
{
    double op2;
    if (strcmp(s, 'sin') == 0)
        push(sin(pop()));
    else if(strcmp(s, 'exp') == 0)
        push(exp(pop()));
    else if(strcmp(s, "pow") == 0)
    {
        op2 = pop();
        push(pow(pop(), op2));
    } else 
        printf("not supported %s\n", s);
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f){
    if (sp < MAXVAL)
        val[sp++] = f;
    else 
        printf("error: stack full, cant't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else 
        printf("error: stack empty\n");
        return 0.0;
}

#include <ctype.h>
int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i, c, d;
    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
    {
        d = getch();
        if (d == ' ' || d == '\t' || d == '\n')
    }
}