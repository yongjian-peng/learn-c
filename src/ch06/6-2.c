/**
 * @file 6-2.c 统计输入中所有单词出现的次数，预先不知道出现的单词列表
 * 编写一个程序，用以读入一个C语言程序，并按照字母顺序分组打印变量名。
 * 要求每一组内各变量名的前个字符相同，其余字符不同，字符串和注释中的单词不予考虑
 * 请将6作为一个可在命令行中设定的参数
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-18
 * 
 * @copyright Copyright (c) 2023
 * command now is the time for all good men to come to the aid of their party
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
int getword(char *word, int lim);

int main() {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while(getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *strdup_(char *s);
/* addtree: 在p或p的下方增加一个节点w */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if (p == NULL) { /* 新单词 */
        p = talloc(); /* 创建一个新节点 */
        p->word = strdup_(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++; /* 重复的单词 */
    else if (cond < 0) /* 小于该节点的单词进入左子树 */
        p->left = addtree(p->left, w);
    else   
        p->right = addtree(p->right, w);
    return p;
}
/* treeprint: 中序打印树p */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup_(char *s) {
    char *p;
    p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int getch(void);
void ungetch(int c);

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/* getch: 取一个字符（可能是压回的字符） */
int getch(void) {
    return bufp > 0 ? buf[--bufp] : getchar();
}

/* ungetch: 把字符压回到输入中 */
void ungetch(int c) {
    if (bufp >= BUFSIZE) 
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getword: 从输入中读取下一个单词或者字符 */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while(isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if(!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}