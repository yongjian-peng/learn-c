/**
 * @file 6-5.c 编写函数 undef 它将从由lookup和install维护的表中删除一个变量及其定义
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

struct nlist {
    struct nlist *next;  /* 链表中的下一项 */
    char *name;  /* 定义的名字 */
    char *defn;  /* 替换文本 */
};

#define HASHSIZE 101
unsigned hash(char *s);
struct nlist *lookup(char *);
struct nlist *install(char *name, char *defn);
static struct nlist *hashtab[HASHSIZE]; /* 指针表 */
void undef(char *name);

char *strdup_(char *);

int main() {
    assert(lookup("IN") == NULL);

    install("IN", "1");
    install("OUT", "0");
    assert(strcmp(lookup("IN")->defn, "1") == 0);
    assert(strcmp(lookup("OUT")->defn, "0") == 0);

    install("IN", "2");
    assert(strcmp(lookup("IN")->defn, "2") ==0);

    undef("IN");

    assert(lookup("IN") == NULL);
    return 0;
}


/* hash: 为字符串s生成哈希值 */
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

/* strdup_: 复制s到某个位置（下划线避免与（string.h）中的strdup冲突）*/
char *strdup_(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1); /* +1是为了'\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* install: 将（name, defn）加入到hashtab中 */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* 不存在 */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup_(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else 
        free((void *) np->defn); /* 释放 defn */

    if ((np->defn = strdup_(defn)) == NULL)
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
        for (; p->next; p = p->next) {
            if (strcmp(name, p->next->name) == 0) {
                temp = p->next;
                p->next = temp->next;
                free(temp);
            }
        }   
}