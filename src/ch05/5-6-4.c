#include <stdio.h>
#include <ctype.h>

int atoi(char *s);

int main()
{
    int s = atoi("+432-4abv");
    printf("%d\n", s);
    return 0;
}

int atoi(char *s) {
    int n, sign;
    for (; isspace(*s); s++);
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for(n = 0; isdigit(*s); s++)
        n = 10 * n + *s - '0';
    return sign * n;
}