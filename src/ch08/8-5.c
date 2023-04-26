/**
 * @file 8-5.c 标准库函数 mcalloc()
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 引用自：https://blog.csdn.net/m0_46655998/article/details/105864213
 * 编译报错，目前还没有能力解决这个问题 使用的是 vscode 自动运行的，vscode 配置运行c 代码不清楚配置的方法，其他的是能运行的。
 */
#include <stdio.h>
#include <unistd.h>

#define NALLOC 1024

typedef double Align; /* 该系统中double为最受限类型 */

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};/* header联合的大小为所占空间最大的成员的大小，即最受限类型的大小 */

typedef union header Header;

static Header base; /* base 是整个空闲块链表的头部 */
static Header *freep = NULL; /* freep 指向上一次完成操作时的上一块 */

void *malloc(unsigned nbytes);
static Header *moreroce(unsigned nu);
void free(void *ap);

int main() {
    int *p;
    int i;
    if ((p = (int *) malloc(100 * sizeof(int))) == NULL)
        return -1;
    for (i = 0; i < 100; i++) {
        *(p + i) = (i + 1) * 2;
    }

    for (i = 0; i < 100; i++) {
        printf("%d", *(p + i));
        if (i % 10 == 9) 
            printf("\n");
    }
    free(p);
    return 0;
}

void *malloc(unsigned nbytes) {
    Header *p, *prevp; /* p指向当前块，prevp指向上一块 */
    Header *moreroce(unsigned);
    unsigned nunits; /* 实际所需空间大小，以一个Header大小为单位 */

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    /* 以向上舍入（大于等于该数的最小整数）的方式计算实际需求的空间大小，加上一个Header大小是因为c中的除法是采用向下舍入的方式计算结果 */
    /* 为了防止nbytes是Header大小的整数倍数时，向上舍入所得结果会比预期值大1，因此还需要进行-1操作，商的结果表示一个头部 */

    /* 每次进入malloc函数时，将prevp指向上一次退出函数时返回的块的上一块，如果第一次进入该函数，那么就为NULL */
    if((prevp = freep) == NULL) {
        base.s.ptr = prevp = freep = &base; /* 第一次进入函数时设置freep和prevp指向base，同时base的ptr成员指向自身，构成一个闭合的链表 */
        base.s.size = 0;
    }

    /* 更新条件为当前块变成上一块，而当前块的下一块变为当前块 */
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if(p->s.size >= nunits) {
            if (p->s.size == nunits) 
                prevp->s.ptr = p->s.ptr; /* 让上一块的ptr直接指向当前块的下一块 */
            else {
                p->s.size -= nunits; /* 当前块的大小减少nunits */
                p+= p->s.size; /* 返回当前块的尾部 */
                p->s.size = nunits; /* 标准返回的块的大小 */
            }
            freep = prevp; /* 保留返回块的上一块指针 */
            return (void *)(p + 1); /* 只返回当前块空闲空间，不返回头部 */
        }
        if(p == freep) /* p是从freep所指向的块的下一块开始的，如果再次回到freep，说明整个链表已经完成一轮搜索，没有找到大于或等于所需空间的块 */
            if ((p = moreroce(nunits)) == NULL) /* 调用moreroce 函数请求系统分配空间，并让p指向分配的块的上一块 */
                return NULL;
    }
}

static Header *moreroce(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC) /* 一次调用至少分配NALLOC个Header大小空间 */
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) - 1) /* sbrk 返回-1时 返回NULL */
        return NULL;
    up = (Header *) cp; /* 以Header大小为单位分配的空间进行处理 */
    up->s.size = nu;

    free((void *) (up + 1)); /* 设置完头部之后，调用free函数将头部后面的空间插入到空闲区域 */
    return freep; /* 完成freep操作后，freep指向的是分配块的上一块 */
}

void free(void *ap) {
    Header *bp, *p;/* bp指向待释放的块，p指向当前块 */
    bp = (Header *) ap - 1; /* 回到块的头部 */

    /* 由于块的排列是根据块的地址递增顺序，从freep所指的块开始循环，直到待释放的地址大于当前块并且小于当前块的下一块是退出循环 */
    for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) /* 还有一种情况是，待释放的块的地址大于链表的最后一块，或者小于链表的第一块 */
            break;
    
    /* 如果待释放块紧邻当前块的下一块 */
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.ptr = p->s.ptr->s.ptr; /* 将待释放块的ptr指向当前块的下一块的下一块 */
        bp->s.size += p->s.ptr->s.size; /* 合并待释放块和当前块的下一块 */
    }
    else 
        bp->s.ptr = p->s.ptr; /* 否则将待释放块的ptr指向当前块的下一块 */
    
    if (p + p->s.size == bp) { /* 如果当前块与待释放的块紧邻 */
        p->s.ptr = bp->s.ptr; /* 将当前块的ptr指向待释放块的下一块 */
        p->s.size += bp->s.size; /* 合并当前块和待释放的块 */
    }
    else    
        p->s.ptr = bp; /* 否则将当前块的ptr指向待释放块 */

    /* 如果待释放与当前块和当前块的下一块都不紧邻，那么就先执行第一个else 再执行第二个 else 同时待释放块的size不改变 两个 if-else 语句不能调换顺序 */

    freep = p; /* freep指向当前块 */
}