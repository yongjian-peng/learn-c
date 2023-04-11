/*此题与上一题的区别不大，可以将上一题看做m = 1，即从第1列开始，每隔n列停
止，也就是说此题正在上一题的基础上需要添加一个判断，m列之前的部分不用更改*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1000
#define Tabsize 8//制表符的长度时固定的，在本系统中其长度为8个字符
 
int getline(char line[], int maxline);
void detab(char *s, char *t, int tabsize, int m);
void entab(char *s, char *t, int tabsize, int m);
 
int main(int argc, char *argv[])
{
	char origin[MAXLINE];
	char result[MAXLINE];
	int tabsize;
	int m;

	if(argc == 1)
	{
		m = 1;
		tabsize = Tabsize;
	}
	else if(argc == 3)
	{
		while(--argc)
		{ 
			// *++(*argv) 字符数组 当前元素向后移动 元素内字符的第一个字符
			// **argv 字符数组 当前下标 下标中的第0个字符
            printf("*++argv%p", *++argv);
            printf("*(*++argv)%p", *(*++argv));
			if(*(*++argv) == '-' && isdigit(*++(*argv)))
				m = atoi(*argv);
			else if(**argv == '+' && isdigit(*++(*argv)))
				tabsize = atoi(*argv);
			else
			{
				printf("parameter error\n");
				return -1;
			}
		}
	}
	else
	{
		printf("error!\n");
		return -1;
	}

	printf("请输入带制表符的字符串：\n");
	while(getline(origin, MAXLINE) > 0)
	{
		detab(origin, result, tabsize, m);
		printf("detab : \n%s\n", result);

		printf("请输入带空格的字符串：\n");
		getline(origin, MAXLINE);
		entab(origin, result, tabsize, m);
		printf("entab : \n%s\n", result);

		printf("继续输入带制表符的字符串\n");
	}
	return 0;
}
 
void detab(char *s, char *t, int tabsize, int m)
{
	int all, size;//all统计字符数，size计算制表符到制表符终止位占多少字符位

	for(all = 0, size = 0; *s; s++)
	{
		if(*s == '\t' && (all >= (m - 1)))
		{
			size = tabsize - (all % tabsize);//计算需要多少个空格填充制表符所占字符长度
			while(size > 0)
			{
				*t++ = ' ';
				all++;
				size--;
			}
		}
		else if(*s == '\t')//当制表符出现在m列之前时，保留制表符，同时统计制表符所占字符位
		{
			size = tabsize - (all % tabsize);
			while(size > 0)
			{
				all++;
				size--;
			}
			*t++ = '\t';
		}
		else
		{
			*t++ = *s;
			all++;
		}
	}
	*t = *s;
}
void entab(char *s, char *t, int tabsize, int m)
{
	int all, space;//all统计字符数，space记录使用制表符后还需要使用多少个空格
	for(all = 0, space = 0; *s; s++)
	{
		if(*s == ' ' && (all >= (m - 1)))
		{
			if(all % tabsize != tabsize - 1)
				space++;//标记空格数

			else if(all % Tabsize == tabsize - 1)//每经过一次制表符的终止位就打印一次制表符
			{
				space = 0;//将空格数清零
				*t++ = '\t';
			}
			all++;
		}
		else
		{
			if(space > 0)//当空格没有超过制表符终止位时，打印空格
			{
				while(space > 0)
				{
					*t++ = ' ';
					space--;
				}
			}
			*t++ = *s;
			all++;
		}
	}
	*t = *s;
}

int getline(char s[], int lim)
{
	int c, i;
 
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
 
	s[i] = '\0';
	return i;
}
