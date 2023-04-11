#include <stdio.h>
#include <string.h>

void reverse(char *s);

int main() {
    char str[] = "abcdef";

    reverse(str);
    printf("%s\n", str);
    return 0;
}

void reverse(char *s) {
    int c;
    char *t;

    for(t = s + (strlen(s) - 1); s < t; t--, s++)
    {
        c = *s;
        *s = *t;
        *t = c;
    }
}