/**
 * @file 8-6.c 标准库 calloc(n, size)返回一个指针，它指向n个长度wei size 的对象，且所有分配的存储空间都被初始化为0，通过调用或修改malloc函数实现 calloc函数
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*不管是修改还是调用malloc函数，主要需要解决的是两个问题：
  根据传递的参数计算所需空间大小、将分配的存储空间初始化为0 */
 #include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NALLOC 1024

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

void *calloc(unsigned n, unsigned size);
static Header *moreroce(unsigned nu);
void free(void *ap);

int main(void)
{
	int *p;
	int i;
	if((p = (int *) calloc(100, sizeof(int))) == NULL)
		return -1;

	for(i = 0; i < 100; i++)
		*(p + i) = (i + 1) * 2;

	for(i = 0; i < 100; i++)
	{
		printf("%d", *(p + i));
		if(i % 10 == 9)
			putchar('\n');
	}
	free(p);
	return 0;
}

void *calloc(unsigned n, unsigned size)
{
	Header *p, *prevp;
	Header *moreroce(unsigned);
	unsigned nunits;

	nunits = ((n * size) + sizeof(Header) - 1) / sizeof(Header) + 1;//计算所需空间大小
	
	if((prevp = freep) == NULL)
	{
		base.s.ptr = prevp = freep = &base;
		base.s.size = 0;
	}

	for(p = prevp -> s.ptr; ; prevp = p, p = p -> s.ptr)
	{
		if(p -> s.size >= nunits)
		{
			if(p -> s.size == nunits)
				prevp -> s.ptr = p -> s.ptr;
			else
			{
				p -> s.size -= nunits;
				p += p -> s.size;
				p -> s.size = nunits;
			}
			freep = prevp;

			memset(p + 1, 0x00, n * size);//存储空间初始化方式有两种：利用循环、利用memset函数，后者相对方便一点
			//memset函数将第一个参数为指针s，第二参数为待替换字符c，第三个参数为替换数量n
			//memset函数将s中的前n个字符替换为c，并返回s
			return (void *)(p + 1);
		}
		if(p == freep)
			if((p = moreroce(nunits)) == NULL)
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
	
	if(cp == (char *) -1)
		return NULL;
	up = (Header *) cp;
	up -> s.size = nu;
	
	free((void *) (up +1));
	return freep;
}

void free(void *ap)
{
	Header *bp, *p;
	bp = (Header *) ap - 1;
	
	for(p = freep; !(bp > p && bp < p -> s.ptr); p = p -> s.ptr)
		if(p >= p -> s.ptr && (bp > p || bp < p -> s.ptr))
			break;

	if(bp + bp -> s.size == p -> s.ptr)
	{
		bp -> s.ptr = p -> s.ptr -> s.ptr;
		bp -> s.size += p -> s.ptr -> s.size;
	}
	else
		bp -> s.ptr = p -> s.ptr;

	if(p + p -> s.size == bp)
	{
		p -> s.ptr = bp -> s.ptr;
		p -> s.size += bp -> s.size;
	}
	else
		p -> s.ptr = bp;
	freep = p;
}
