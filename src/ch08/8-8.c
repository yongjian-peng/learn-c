/**
 * 编写函数 bfree(p,n) 释放一个包含n个字符的任意块，并将它放入由malloc 和 free 维护的空间链表中，通过
 * 使用bfree 用户可以在任意时刻项空块链表中添加一个静态或外部数组
 * bfree函数和moreroce函数并没有太大区别，只是缺少向系统请求空间的步骤
 */
#include <stdio.h>
#include <unistd.h>

#define NALLOC 1024
#define N '\n'

typedef double Align;

union header {
    struct
    {
        union header *ptr;
        unsigned size;
    } s;
    Align x;    
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *malloc3(unsigned nbytes);
static Header *moreroce(unsigned nu);
void free3(void *ap);
void bfree(void p, unsigned n);

int main(void) {
    int *p;
    int i;
    if((p = (int *) malloc3(100 * sizeof(int))) == NULL)
        return -1;

    for (i = 0; i < 100; i++)
        *(p + i) = (i + 1) * 2;
    
    for (i = 0; i < 100; i++) {
        printf("%d ", *(p + i));
        if(i % 10 == 9) 
            putchar(N);
    }
    free3(p);
    return 0;
}

void *malloc3(unsigned nbytes) {
    Header *p, *prevp;
    Header *moreroce(unsigned);
    unsigned nunits;

    if (nbytes <= 0) {
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
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
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

static Header *moreroce(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;
    
    if(nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) -1);
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;

    free3((void *) (up + 1));
    return freep;
}

void free3(void *ap)
{
    Header *bp, *p;
    bp = (Header *) ap - 1;

    if (ap == NULL || bp->s.size <= 0)
    {
        fprintf(stderr, "error: pointer is empty\n");
        return;
    }

    for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
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

void bfree(void p, unsigned n) {
    Header *up;
    unsigned nunits;

    nunits = (n - sizeof(Header)) / sizeof(Header); /* 预留出一个头部大小的空间，其余部分作为空闲空间 */

    if (p == NULL || n <= 0)
    {
        fprintf(stderr, "error: pointer is empty\n");
        return;
    }

    up = (Header *)p;
    up->s.size = nunits;
    free3((void *) (up + 1)); /* 调用free3函数将空闲空间插入空闲区域 */
}
