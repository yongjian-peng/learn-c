#include <stdio.h>

void strcpy1(char *s, char *t);
void strcpy2(char *s, char *t);

int strcmp1(char *s, char *t);
int strcmp2(char *s, char *t);

void strcpy1(char *s, char *t)
{
    int i;
    i = 0;
    while((s[i] = t[i]) != '\0')
        i++;
}

void strcpy2(char *s, char *t)
{
    // int i;
    // i = 0;
    // while((*s = *t) != '\0')
    //     s++;
    //     t++;
    // while ((*s++ = *t++) != '\0')
    //     ;
    while (*s++ = *t++)
        ; 
}

int strcmp1(char *s, char *t){
    int i;
    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}

int strcmp2(char *s, char *t)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

int main() {
    char s[] = "thisist";
    char t[] = "thisisydff";

    strcpy2(s, t);
    printf("%s", s);

    int i;
    i = strcmp2(s, t);
    printf("%d", i);
    return 0;
}