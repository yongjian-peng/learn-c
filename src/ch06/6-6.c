#include <stdio.h>
#include <string.h>

/**
 * @file 6-6.c 以本节介绍函数为基础，编写一个适合C语言程序使用的#define 处理器的简单版本
 * 即无参数的情况，你会发现 getch 和 ungetch 函数非常有用
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#define BUFSIZE 100
#define MAXWORD 100
#define HASHSIZE 101

char buf[BUFSIZE];
int bufp = 0;

/* 链表项 */
struct nlist {
    struct nlist *next; /* 链表中的下一项 */
    char *name; /* 定义的名字 */
    char *defn; /* 替换文本 */
}

int getch(void);
void ungetch(int c);

int getword(char *word, int lim, int skip_space);
int get_definition(char definition[], int lim);

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);

static struct nlist *hashtab[HASHSIZE]; /* 指针表 */

char *strdup_(char *s);

int main() {
    char word[MAXWORD], definition[MAXWORD];
    int len;
    struct nlist *p;

    while(getword(word, MAXWORD, 0) != EOF)
        if (strcmp(word, "#define") == 0) {
            getword(word, MAXWORD, 1);
            len = get_definition(definition, MAXWORD);
            definition[len - 1] = '\0';
            install(word, definition);
        }
        else if (strcmp(word, "#undef") == 0) {
            getword(word, MAXWORD, 1);
            undef(word);
        }
        else if (word[0] == '\n')
            putchar('\n');
        else if ((p = lookup(word)) != NULL)
            printf("%s ", p->defn);
        else    
            printf("%s ", word);
    return 0;
}

/* strdup: 复制s到某个位置 */
char *strdup_(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1是为了'\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* getword: 从输入中读取下一个单词或字符，跳过字符常量、注释及预处理器控制指令，下划线视为单词的一部分 */
int getword(char *word, int lim, int skip_space) {
    int c, next = '\0';
    char *w = word;

    c = getch();
    if (skip_space)
        while(isspace(c))
            c = getch();
}

