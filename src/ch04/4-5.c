/**
 * @file 4-5.c 给计算器程序增加访问 sin、exp、与pow 等库函数的操作
 * 有关这些库函数的详细信息 参见附录B.4节中的头文件<math.h>.
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023
 * url https://blog.csdn.net/carolAIF/article/details/83672348
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100

#define TRUE 1
#define FALSE 0

#define NUMBER 0
#define IDENTIFIER 1

int Getop(char s[]);
void push(double val);
double pop(void);
void showTop(void);
void duplicate(void);
void swapItems(void);
void clearStack();
void dealWithName(char s[]);

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];
    int flag = TRUE;

    while ((type = Getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case IDENTIFIER:
            dealWithName(s);
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
            if (op2)
                push(pop() / op2);
            else
                printf("\nError: division by zero!");
            break;
        case '%':
            op2 = pop();
            if (op2)
                push(fmod(pop(), op2));
            else
                printf("\nError: division by zero!");
            break;
        case '?':
            showTop();
            break;
        case '#':
            duplicate();
            break;
        case '~':
            swapItems();
            break;
        case '!':
            clearStack();
        case '\n':
            printf("\n\t%.8g\n", pop());
            break;
        default:
            printf("\nError: unknown command %s.\n", s);
            break;
        }
    }
    return EXIT_SUCCESS;
}

#define MAXVAL 100

int sp = 0;         /* Next free stack position. */
double val[MAXVAL]; /* value stack. */

/* push: push f onto stack. */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("\nError: stack full can't push %g\n", f);
}

/*pop: pop and return top value from stack.*/
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("\nError: stack empty\n");
        return 0.0;
    }
}

void showTop(void) //?
{
    double top = val[sp];

    printf("%f\n", top);
}

void duplicate(void) // #
{
    int top = sp - 1;
    double topVal;
    topVal = val[top];
    val[top + 1] = topVal;
    sp++;
}

void swapItems(void) //~
{
    double temp;
    int top = sp;
    int secTop = sp - 1;
    temp = val[top];
    val[top] = val[secTop];
    val[secTop] = temp;
}

/* pop only returns a value if sp is greater than zero. So setting the
stack pointer to zero will cause pop to return its error */

void clearStack(void) //!
{
    sp = 0;
}

/* deal with a string/name this may be either a maths function or for
future exercises: a variable */
void dealWithName(char s[])
{
    double op2;

    if (0 == strcmp(s, "sin"))
        push(sin(pop()));
    else if (0 == strcmp(s, "cos"))
        push(cos(pop()));
    else if (0 == strcmp(s, "exp"))
        push(exp(pop()));
    else if (!strcmp(s, "pow"))
    {
        op2 = pop();
        push(pow(pop(), op2));
    }
    else
        printf("%s is not a supported function.\n", s);
}

int getch(void);
void unGetch(int);

/* Getop: get next operator or numeric operand. */
int Getop(char s[])
{
    int i = 0;
    int c;
    int next;

    /* Skip whitespace */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    // 如果读入的是标识符...字母
    if (isalpha(c))
    {
        i = 0;
        while (isalpha(s[i++] = c))
            c = getch();
        s[i - 1] = '\0';
        if (c != EOF)
            unGetch(c);
        return IDENTIFIER;
    }

    /* Not a number but may contain a unary minus. */
    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    if (c == '-')
    {
        next = getch();
        if (!isdigit(next) && next != '.')
        {
            return c;
        }
        c = next;
    }
    else
        c = getch();

    while (isdigit(s[++i] = c))
        c = getch();
    if (c == '.') /* Collect fraction part. */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        unGetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/* Getch: get a ( possibly pushed back) character. */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* unGetch: push character back on input. */
void unGetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("\nUnGetch: too many characters\n");
    else
        buf[bufp++] = c;
}