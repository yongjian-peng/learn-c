/*关于字段处理的部分有点费解，我认为的字段处理是类似于excel表那样，假设有
两行输入，行1为123456781234，行2为567812345678，字段宽度为4，假设按照第一
个字段宽度排序，行1在前，行2在后，假设按照第二个字段宽度排序，行2在前，行1
灾后，假设没有指定按照那个字段排序，那就默认采用第一个字段宽度，而如果输入
行的字段宽度小于指定的字段宽度，即假设按照第四个字段宽度，上面两行都只有三
个字段宽度，此时采用默认的第一个字段宽度
采用结构来实现上面的要求是非常方便的，但是还没学，所以还是跟着书本来
重新写一个，上面的程序再添就有点乱了，改也不好改
*/
#include <stdio.h>
#include <string.h>

#define MAXLINES 100
#define MAXLEN 1000
#define ALLOCSIZE 10000
#define SIZE 4//定义一个字段宽度为4个字符

char allocbuf[ALLOCSIZE];
char *lineptr[MAXLINES];
char *allocp = allocbuf;

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
int getlines(char s[], int lim);
void qsort(char *lineptr[], int left, int right, int (*comp)(const char *, const char *, int ), int size);
int sizecmp(const char *s, const char *t, int size);
void swap(char *v[], int i, int j);
char *alloc(int n);
void afree(char *p);

int main(int argc, char *argv[])
{
	int nlines;
	int size = 1;

	if(argc == 2)
	{
		if(!strcmp(argv[1], "-s"))
		{
			printf("请输入按照哪个字段宽度排序\n");
			scanf("%d", &size);
		}
	}


	if((nlines = readlines(lineptr, MAXLINES)) > 0)
	{
		qsort(lineptr, 0, nlines - 1, sizecmp, size);
		writelines(lineptr, nlines);
	}
	else
	{
		printf("input is empty!\n");
		return -1;
	}

	afree(allocbuf);
	return 0;
}

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while((len = getlines(line, MAXLEN)) > 0)
	{
		if(nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else
		{
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

char *alloc(int n)
{
	if(allocp + n <= allocbuf + ALLOCSIZE)
	{
		allocp += n;
		return allocp - n;
	}
	else
		return NULL;
}

int getlines(char s[], int lim)
{
	int c, i;

	for(i = 0; i < lim -1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;

	if(c == '\n')
		s[i++] = '\n';

	s[i] = '\0';
	return i;

}

void qsort(char *v[], int left, int right, int (*comp)(const char *, const char *, int ), int size)
{
	int i, last;

	void swap(char *v[], int, int);

	if(left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;

	for(i = left + 1; i <= right; i++)
		if((*comp) (v[i], v[left], size) < 0)
			swap(v, ++last, i);
	
	swap(v, left, last);
	qsort(v, left, last - 1, comp, size);
	qsort(v, last + 1, right, comp, size);
}

int sizecmp(const char *s, const char *t, int size)
{
	int length = (size - 1) * SIZE;
	const char *v1, *v2;
	v1 = s;
	v2 = t;

	if(length == 0)
		return strcmp(s, t);

	while(length > 0 && *v1 != '\0' && *v2 != '\0')
	{
		v1++;
		v2++;
		length--;
	}
	if(*v1 == '\0' || *v2 == '\0')
	{
        // int strcmp(const char *str1, const char *str2) 把str1 所指向的字符串和str2所指向的字符串进行比较
		return strcmp(s, t);
	}
	else
	{
		return strcmp(v1, v2);
	}
}

void swap(char *v[], int i, int j)
{
	char *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void writelines(char *lineptr[], int nlines)
{
	for(int i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void afree(char *p)
{
	if(allocbuf <= p && p >= allocbuf + ALLOCSIZE)
		allocp = p;
}
//程序比较简陋，但是基本能实现要求
