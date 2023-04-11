/*
    5-2 模仿函数 getint 的实现方法，编写一个读取浮点数的函数 getfloat getfloat 函数的
    返回值应该是什么类型
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 10
#define BUFSIZE 10

int getch();
void ungetch(int c);
int getfloat(float *pn);

char buffer[BUFSIZ];
int bufp;

int main() {
    int n;
    float array[SIZE];

    for (n = 0; n < SIZE; n++)
    {
        array[n] = rand();
    }
        
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++) {
        // if (c == 0)
        // {
        //     getch();
        //     n--;
        // }
    }
    for (n = 0; n < SIZE; printf("%.2f ", array[n++]))
        ;
}


/* int main() {
    int n;
    float c, array[SIZE] = {0};

    // for (n = 0; n < SIZE; array[n++] = 0)
    //     ;
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++) {
        if (c == 0)
        {
            getch();
            n--;
        }
    }
    for (n = 0; n < SIZE; printf("%.2f ", array[n++]))
        ;
} */

int getfloat(float *pn)
{
    int c, sign;
    float power;
    // while(isspace(c = getch()));
    if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') 
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for(*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + c - '0';
    if (c == '.')
        c = getch();
    for(power = 10.0; isdigit(c); c = getch(), power *= 10.0)
        *pn += (c - '0') / power;
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int getch() {
    printf("getch bufp %d\n", bufp);
    return (bufp > 0) ? buffer[--bufp] : getchar();
}

void ungetch(int c) {
    printf("ungetch bufp %d\n", bufp);
    printf("ungetch buffer %d\n", buffer);
    if (bufp >= BUFSIZE) 
        printf("oversized...\n");
    else  
        buffer[bufp++] = c;
} 