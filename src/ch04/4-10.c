
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF)
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
                push(pop() * pop());
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
                    printf("error: zeor divisor\n");
                break;
            case '\n':
                printf("\t%.8g", pop());
                break;
            default:
                printf("error: unknow command %s\n", s);
                break;
            }
    }
    return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, cant't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }  
}

#include <ctype.h>
#define MAXLINE 1000
char line[MAXLINE];
int linep = 0;
int lineLen;

int getop(char s[])
{
    int i, c;
    int getline1(char s[], int lim);
    if(linep == 0)
        lineLen = getline1(line, MAXLINE);
    if (lineLen == 0)
        return EOF;
    else
    {
        while((s[0] = c = line[linep++]) == ' ' || c == '\t')
            ;
        s[1] = '\0';
        if (linep >= lineLen)
            linep = 0;
        if (!isdigit(c) && c != '.')
            return c;
        i = 0;
        if (isdigit(c))
            while(isdigit(s[++i] = c = line[linep++]))
                ;
        if (c == '.')
            while(isdigit(s[++i] = c = line[linep++]))
                ;
        linep--;
        s[i] = '\0';
        if(linep >= lineLen)
            linep = 0;
        return NUMBER;
    }
}

int getline1(char s[], int lim)
{
    int c, i;
    i = 0;
    while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return 0;
}