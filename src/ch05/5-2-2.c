#include <stdio.h>

char *alloc(int n);
void afree(char *p);

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    // 这里allocbuf 的值 是固定的 
    printf("allocbuf %d\n", allocbuf);
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else 
        return 0;
}

void afree(char *p) {
    printf("in afree: %d\n", p);
    printf("in afree: %s\n", p);
    printf("in afree: %p\n", p);
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE){
        allocp = p;
    }
    printf("in afree: %d\n", allocp);
    printf("in afree: %s\n", allocp);
    printf("in afree: %p\n", allocp);
}

int main() {
    char *pa;
    pa = alloc(5000);
    printf("*pa %c\n", pa);
    printf("*pa %d\n", pa);
    pa = alloc(3000);
    printf("*pa %c\n", pa);
    printf("*pa %d\n", pa);
    pa = alloc(1000);
    printf("*pa %c\n", pa);
    printf("*pa %d\n", pa);
    //  pa = alloc(1000);
    // printf("*pa %c\n", pa);
    // printf("*pa %d\n", pa);
    //  pa = alloc(1000);
    // printf("*pa %c\n", pa);
    // printf("*pa %d\n", pa);

    char s = 'g';

    char *fe;
    fe = &s;
    afree(fe);
    printf("*afree %d\n", *allocp);

    afree(fe);
    printf("*afree %d\n", *allocp);
    
    return 0;
}