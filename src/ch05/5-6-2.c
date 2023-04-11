#include <stdio.h>

int strindex(char *s, char *t);
char pattern[] = "ould";

int main() {

    char str[] = "aouldabc";
    int j;
    j = strindex(str, pattern);

    printf("%d\n", j);

    return 0;
}

int strindex(char *s, char *t)
{
    char *bs = s;
    char *bt = t;
    int i;
    for(i = 0; *s != '\0'; s++, i++) {
        for (bs = s, bt = t; *bt != '\0' && *bs == *bt; bs++, bt++)
            ;
        if (*t != '\0' && *bt == '\0')
            return i;
    }
    return -1;
}