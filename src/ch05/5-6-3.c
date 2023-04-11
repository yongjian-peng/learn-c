#include <stdio.h>

#define MAXLINE 100

int getline2(char *line, int max);

int main() {
    char line[MAXLINE];

    int get;
    get = getline2(line, MAXLINE);

    printf("%d\n", get);

    return 0;
}

int getline2(char *s, int max) {
    int c;
    char *t = s;

    while(--max && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - t;
}