#include <stdio.h>
#include <string.h>
/**
 * @brief 重写函数 readlines 将输入的文本行存储到有 main 函数提供的一个数组中
 * 而不是存储到调用 alloc 分配的存储空间中，该函数的运行速度比改写前快多少？
 * 
 */
#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main() {
    lineptr[0] = "123";
    lineptr[1] = "1236";
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}
#define MAXLINE 1000
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines2;
    char *p, line[MAXLINE];

    nlines2 = 0;
    while((len = getline(line, MAXLINE)) > 0) {
        p = alloc(len);
        if (nlines2 >= maxlines || p == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines2++] = p;
        }
    }
        
        
    return nlines2;
}

/* writelines; write output lines */
// void writelines(char *lineprt[], int nlines)
// {
//     int i;
//     for (i = 0; i < nlines; i++)
//         printf("%s\n", lineprt[i]);
// }

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
    {
        /* code */
        printf("%s\n", *lineptr++);
    } 
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}