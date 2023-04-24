/**
 * @file fsize.c 修改 fsize 程序 打印 i 节点项包含的其他信息
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-24
 * 
 * @copyright Copyright (c) 2023
 * 文章出自于 https://blog.csdn.net/m0_46655998/article/details/105864213
 */
/*
由于我的系统不是UNIX系统，所以这个程序我也不知道具体的运行结果，但是我输入文件名（不是目录）时，结果是正常的

UNIX系统中，目录是一个文件，它包含一个文件名列表和这些文件的i结点索引号，而i结点存储的是文件的相关信息（即一个stat结构）

也就是说一个目录可以看做是一个结构数组，该数组的每个元素是一个direct结构，结构包含一个文件名和该文件的i结点索引号

由于目录是一个文件，那么就可以使用open函数和read函数打开，传入目录名利用open函数得到文件描述符

传入文件描述符利用read函数每次从目录中读取出文件名和索引号（即一个direct结构）

由于目录中每个文件的文件名是没有空字符的，但是我们读取每个文件时，需要在文件名后加空字符，因此另外声明一个与direct结构
类似的结构Dirent
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

//#include <sys/dir.h>
#define DIRSIZ 14

struct direct {
	ino_t d_ino;//索引号
	char d_name[DIRSIZ];//没有空字符的名
};


#define NAME_MAX 14

typedef struct {
	long ino;//索引号
	char name[NAME_MAX + 1];//名加一个空字符
} Dirent;

typedef struct {
	int fd;//文件描述符
	Dirent d;
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);
void fsize(char *);
void dirwalk(char *, void(*fcn) (char *));

int main(int argc, char **argv)
{
	if(argc == 1)
		fsize(".");//处理当前目录
	else
		while(--argc > 0)
			fsize(*++argv);
	return 0;
}

void fsize(char *name)
{
	struct stat stbuf;//储存i结点信息的结构，该结构的声明在头文件<sys/stat.h>中

	if(stat(name, &stbuf) == -1)//系统调用stat将name文件的i结点信息存储在stbuf中，如果返回值为-1，表示出错
	{
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}

	if((stbuf.st_mode & S_IFMT) == S_IFDIR)//S_IFMT表示文件类型，S_IFDIR表示文件类型为目录
		dirwalk(name, fsize);//遍历目录

	printf("%ld\t%ld\t%d\t%d\t%d\t%d\t%ld\t%8ld\t%ld\t%ld\t%ld\t%s\n",
		stbuf.st_dev, stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink, stbuf.st_uid, stbuf.st_gid, 
		stbuf.st_rdev, stbuf.st_size, stbuf.st_atime, stbuf.st_mtime, stbuf.st_ctime, name);
}

void dirwalk(char *dir, void (*fcn) (char *))
{
	char name[NAME_MAX];
	Dirent *dp;
	DIR *dfd;

	if((dfd = opendir(dir)) == NULL)//opendir函数打开目录，并将信息保存在一个DIR结构中返回，如果出现错误，返回NULL
	{
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}

	while((dp = readdir(dfd)) != NULL)//直到整个目录遍历完
	{
		if(strcmp(dp -> name, ".") == 0 || strcmp(dp -> name, ".."))//如果返回的文件名为"."或".."，为目录本身和父目录，跳过
			continue;
		if(strlen(dir) + strlen(dp -> name) + 2 > sizeof(name))//文件名过长
			fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp -> name);
		else
		{
			sprintf(name, "%s/%s", dir, dp -> name);
			(*fcn)(name);//递归调用，查看文件是否为目录，如果为目录，继续递进，否则递归回归，继续下一文件
		}
	}
	closedir(dfd);
}

DIR *opendir(char *dirname)
{
	int fd;//文件描述符
	struct stat stbuf;//储存i结点信息的结构
	DIR *dp;

	if((fd = open(dirname, O_RDONLY, 0)) == -1//open函数返回文件描述符
		|| fstat(fd, &stbuf) == -1            //系统调用fstat打开文件，并将文件的i结点信息存储在stbuf中
		|| (stbuf.st_mode & S_IFMT) != S_IFDIR//如果文件类型不是目录
		|| ((dp = (DIR *) malloc(sizeof(DIR))) == NULL)//如果分配内存失败
		)
		return NULL;
	dp -> fd = fd;
	return dp;
}

void closedir(DIR *dp)
{
    printf("closedir");
	if(dp)
	{
		close(dp -> fd);//关闭文件
		free(dp);//释放分配的内存
	}
}

Dirent *readdir(DIR *dp)
{
	struct direct dirbuf;
	static Dirent d;//d是一个static变量，每次退出函数不会销毁，用于储存目录中一个文件的文件名和索引号

	while(read(dp -> fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf))//每次从目录中读取一个direct结构的信息
	{
		if(dirbuf.d_ino == 0)//如果目录位置当前未使用，跳过，读取下一个
			continue;
		d.ino = dirbuf.d_ino;//将索引号与文件名拷贝
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';//在文件名后添加空字符
		return &d;
	}
	return NULL;//如果目录中的信息读取完，就返回NULL
}
