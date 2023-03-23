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
    int len, nlines;
    char *p, line[MAXLINE];

    nlines = 0;
    while((len = getline(line, MAXLINE)) > 0)
        if (nlines >= maxlines || p = alloc(len) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
        }
    return nlines;
}