/**
 * @file 5-13.c编写程序 tail 将其输入的最后 n
 * 行打印出来，默认情况下 n的值为 10 但可通过一个可选参数改变n的值，因此 命令 tail -n
 * 将打印其输入的最后n行，无论输入或n 的值是否合理，该程序都应该正常运行，编写的程序要充分地利用存储空间
 * 输入行的存储方式应该同 5.6 节中排序程序的存储方式一样，而不采用固定长度的二维数组
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 100
#define MAXLEN 1000
#define ALLOCSIZE 10000

char *lineptr[MAXLINES];
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

int readlines(char *lineptr[], int maxlines);
void printlines(char *lineptr[], int n, int nlines);
int getline(char s[], int lim);
char *alloc(int n);
void afree(char *p);

int main(int argc, char *argv[])
{
    int n;
    int nlines = 0;
    if (argc == 2) {
        if(*(*++argv) == '-' && isdigit(*++(*argv)))
            n = atoi(*argv);
        else if(isdigit(**argv))
            n = atoi(*argv);
        else
            n = 10;
    } 
    else 
        n = 10;
    
    if ((nlines = readlines(lineptr, MAXLINES)) > 0)
    {
        if (nlines < n)
            printlines(lineptr, 0, nlines);
        else   
            printlines(lineptr, n, nlines);
    }
    else 
    {
        printf("error: input is empty\n");
        return -1;
    }

    afree(allocbuf);
    return 0;
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while((len = getline(line, MAXLEN)) > 0)
    {
        if(nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

// printlines 打印字符数组中的元素
void printlines(char *lineptr[], int n, int nlines)
{
    for(int i = nlines - n; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int getline(char s[], int lim)
{
    int c, i;
    for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

// 分配空间
char *alloc(int n)
{
    if (allocp + n <= allocbuf + ALLOCSIZE)
    {
        allocp += n;
        return allocp - n;
    }
    else 
        return NULL;
}

// 释放空间
void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}