/**
 * @file 4-8.c 假定最多只压回一个字符，请相应地修改getch与ungech这两个函数
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int getch(void);
void ungetch(int c);
void ungets(char s[]);

char buf;
bool bufState = false;


int getch(void)
{
    if(bufState){
        bufState = false;
        return buf;
    } else
        return getchar();
}

void ungetch(int c)
{
    if(!bufState)
    {
        buf = c;
        bufState = true;
    }
    else
        printf("buf is full\n");
}

void ungets(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        ungetch(s[i]);
    }
}

int main()
{
    char *s = "hello world!";
    char *s2 = "A test for ungets!";

    int i;
    for (i = 0; s[i] != '\0'; i++)
    {
        ungetch(s[i]);
    }
    ungets(s2);

    printf("%c\n", buf);
    return 0;
}