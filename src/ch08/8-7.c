/**
 * @file 8-7.c malloc 接收对存储空间的请求时，并不检查请求长度的合理性，而free函数则认为被释放的块包含一个有效长度字段，改进这些函数，使他们具有检查错误的功能
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 引用自：https://blog.csdn.net/m0_46655998/article/details/105864213
 * 
 */
#include <stdio.h>
#include <unistd.h>

#define NALLOC 1024
#define N '\n'

typedef double Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *malloc2(unsigned nbytes);
static Header *moreroce(unsigned nu);
void free2(void *ap);

int main(void) {
    int *p;
    int i;
    if ((p = (int *) malloc2(100 * sizeof(int))) == NULL)
        return -1;
    for (i = 0; i < 100; i++)
        *(p + i) = (i + 1) * 2;

    for (i = 0; i < 100; i++) {
        printf("%d ", *(p + i));
        if (i % 10 == 9)
            putchar(N);
    }
    free2(p);
    return 0;
}

void *malloc2(unsigned nbytes) {
    Header *p, *prevp;
    Header *moreroce(unsigned);
    unsigned nunits;

    if (nbytes <= 0) { /* malloc2 函数判断错误 */
        fprintf(stderr, "error: Request space size must be a positive integer\n");
        return NULL;
    }

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
        base.s.ptr = prevp = freep = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p+= p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = moreroce(nunits)) == NULL)
                return NULL;
    }
}

static Header *moreroce(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if(nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) -1)
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    
    free2((void *) (up + 1));
    return freep;
}

void free2(void *ap) {
    Header *bp, *p;

    bp = (Header *) ap - 1;

    if (ap == NULL || bp->s.size <= 0) { /* free2函数错误判断 */
        fprintf(stderr, "error: pointer is empty\n");
        return;
    }

    for (p = freep; !(bp > p && p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr)
    {
        bp->s.ptr = p->s.ptr->s.ptr;
        bp->s.size += p->s.ptr->s.size;
    }
    else 
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) 
    {
        p->s.ptr = bp->s.ptr;
        p->s.size += bp->s.size;
    }
    else
        p->s.ptr = bp;
    
    freep = p;
}