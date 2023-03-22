#include <stdio.h>

int strlen2(char *s);

int strlen2(char *s) {
    char *p = s;
    while (*p != '\0')
        p++;
    return p - s;
}

int main() {
    char str[] = "abcdef";
    char *le = str;
    int st;
    st = strlen2(le);
    printf("%d ", st);

    int x = 1, y = 2, z[10];
    int *ip;
    ip = &x;
    printf("ip %d", *ip);
    y = *ip;
    *ip = 0;
    ip = &z[0];

    return 0;
}