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
};

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
            printf("%s", p->defn);
        else    
            printf("%s", word);
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
    if (c != EOF)
        *w++ = c;
    if (!(isalpha(c) || c == '_' || c == '\"' || (c == '/' && (next = getch()) == '*') || c == '#')) {
        *w = '\0';
        if (next)
            ungetch(next);
        return c;
    }

    switch (c)
    {
        case '\"': /* 字符串常量 */
            while((*w++ = c = getch()) != '\"')
                if (c == '\\')
                    *w++ = getch();
            break;
        case '/': /* 注释 */
            *w++ = next;
            *w++ = c = getch();
            while ((*w++ = next = getch()) != '/' || c != '*')
                c = next;
            break;
        case '#': /* 预处理器控制命令 */
            while (isalpha(*w++ = c = getch()))
                ;
            ungetch(c);
            --w;
            break;
        default:
            for (; --lim > 0; w++)
                if (!isalnum(*w = getch()) && *w != '_') {
                    ungetch(*w);
                    break;
                }
            break;
    }

    *w = '\0';
    return word[0];
}

/* get_definition: 将#define 替换文本读入到definition并返回其长度 */
int get_definition(char definition[], int lim) {
    int c, i = 0;

    while(isspace(c = getch()))
        ;
    ungetch(c);
    while(--lim > 0 && (c = getch()) != EOF && c != '\n')
        definition[i++] = c;
    if (c == '\n')
        definition[i++] = c;
    definition[i] = '\0';
    return i;
}

/* hash 为字符串s生成哈希值 */
unsigned hash(char *s) {
    unsigned hashval;
    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: 在hashtab中查找s */
struct nlist *lookup(char *s) {
    struct nlist *np;
    
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

/* install: 将（name, defn）加入到hashtab中 */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if((np = lookup(name)) == NULL) { /* 未找到 */
        np = (struct nlist *) malloc(sizeof(*np));
        if(np == NULL || (np->name = strdup_(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else /* 已存在 */
        free((void *) np->defn); /* 释放前一个defn */
    if((np->defn) = strdup_(defn) == NULL)
        return NULL;
    return np;
}

/* undef: 从hashtab中删除name及其定义 */
void undef(char *name) {
    unsigned hashval = hash(name);
    struct nlist *p = hashtab[hashval], *temp;

    if (p == NULL)
        return;
    else if (strcmp(name, p->name) == 0) {
        hashtab[hashval] = p->next;
        free(p);
    }
    else
        for(; p->next; p = p->next)
            if (strcmp(name, p->next->name) == 0) {
                temp = p->next;
                p->next = temp->next;
                free(temp);
            }
}

/* getch: 取一个字符（可能是压回的字符） */
int getch(void) {
    return bufp > 0 ? buf[--bufp] : getchar();
}

/* ungetch: 把字符压回到输入中 */
void ungetch(int c) {
    if (bufp > BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
