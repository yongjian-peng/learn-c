<<<<<<< HEAD
/*
    5-1 如果符号+或者-的后面紧跟的不是数字，getint函数将把符号视为0的有效表达方式。
    修改该函数，将这种形式的+或者-符号重新写回到输入的流中
    输入 123 a 12 -23 d +a +23 -32
*/
=======
>>>>>>> 1c50bc146abc21a4c7c5400a2ec7c02272879f98
#include <stdio.h>

#define SIZE 3
#define BUFSIZE 1000
char buf[BUFSIZE];
int bufp = 0;
<<<<<<< HEAD

void ungetch(int c)
{
=======
/*
    5-1 如果符号+或者-的后面紧跟的不是数字，getint函数将把符号视为0的有效表达方式。
    修改该函数，将这种形式的+或者-符号重新写回到输入的流中
    输入 123 a 12 -23 d +a +23 -32
*/
void ungetch(int c)
{
    printf("bufp %d\n", bufp);
>>>>>>> 1c50bc146abc21a4c7c5400a2ec7c02272879f98
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int getch(void)
{
<<<<<<< HEAD
=======
    printf("getch bufp: %d\n", bufp);
>>>>>>> 1c50bc146abc21a4c7c5400a2ec7c02272879f98
	return (bufp > 0) ? buf[--bufp] : getchar();
}

int main()
{
    int n, c, array[SIZE] = {0}, getint(int *);
    for (n = 0; n < SIZE && (c = getint(&array[n])) != EOF; n++)
	{
		if (c == 0)
		{
			getch();
			n--;
		}
	}
	for (n = 0; n < SIZE; n++)
		printf("%d ", array[n]);
}

#include <ctype.h>
int getch(void);
void ungetch(int);

int getint(int *pn) {
    int c, d, sign;
    while(isspace(c = getch()));
    if(!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1;
    if(c == '+' || c == '-')
    {
        d = getch();
        if(!isdigit(d))
        {
            if (d == EOF)
                return EOF;
            ungetch(d);
            ungetch(c);
            return 0;
        }
        else 
            c = d;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + c - '0';
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}