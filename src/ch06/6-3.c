/**
 * @file 6-3.编写一个交叉引用程序，打印文档中所有的单词的列表，并且每个单词还有一个列表
 * 记录出现过该单词的行号，对 the end 等非实义单词不予考虑
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-18
 *  这一题运行不正确，后期再看，跳过这一题。
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* 链表节点 */
struct list_node {
    int lineno;
    struct list_node *next;
};

struct list_node *alloc_list_node(void);
void insert_list_node(struct list_node *head, int lineno);
void print_list(struct list_node *head);

/* 二叉树节点 */
struct tree_node {
    char *word;   /* 单词 */
    struct list_node *lineno_list;    /* 该单词出现过的行号列表 */
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node *alloc_tree_node(void);
struct tree_node *add_word(struct tree_node *root, const char *word, int lineno);
void print_tree(struct tree_node *root);

int getword(char *word, int lim);

int getch(void);
void ungetch(int c);

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

#define MAXWORD 100

int main(int argc, char *argv[]) {

    

    struct tree_node *root = NULL;
    char word[MAXWORD];
    int lineno = 1;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = add_word(root, word, lineno);
        else if (word[0] == '\n')
            ++lineno;
    print_tree(root);
    return 0;
}



/* alloc_list_node：创建一个链表节点 */
struct list_node *alloc_list_node(void) {
    return (struct list_node *) malloc(sizeof(struct list_node));
}

/* insert_list_node：将lineno插入有序链表 */
void insert_list_node(struct list_node *head, int lineno) {
    struct list_node *p, *tmp;

    printf("head: %p \n", head);
    printf("lineno: %d \n", lineno);

   for (p = head; p->next && p->next->lineno < lineno; p = p->next)
        ;
    
    tmp = alloc_list_node();
    tmp->lineno = lineno;
    tmp->next = p->next;
    p->next = tmp;
}

/* print_list：打印链表 */
void print_list(struct list_node *head) {
    struct list_node *p;

    for (p = head; p->next; p = p->next)
        printf("%d ", p->next->lineno);
}

/* alloc_tree_node：创建一个二叉树节点 */
struct tree_node *alloc_tree_node(void) {
    return (struct tree_node *) malloc(sizeof(struct tree_node *));
}

/* add_word：将word添加到二叉树中，并将行号插入到对应链表中，返回新的根节点指针 */
struct tree_node *add_word(struct tree_node *root, const char *word, int lineno) {
    int cond;

    if (root == NULL) {
        root = alloc_tree_node();
        root->word = strdup(word);
        root->lineno_list = alloc_list_node();
        // insert_list_node(root->lineno_list, lineno);
        root->left = root->right = NULL;
    }
    else if ((cond = strcmp(word, root->word)) == 0)
        insert_list_node(root->lineno_list, lineno);
    else if (cond < 0)
        root->left = add_word(root->left, word, lineno);
    else
        root->right = add_word(root->right, word, lineno);
    return root;
}

/* print_tree：中序打印二叉树 */
void print_tree(struct tree_node *root) {
    if (root != NULL) {
        print_tree(root->left);
        printf("%s: ", root->word);
        print_list(root->lineno_list);
        putchar('\n');
        print_tree(root->right);
    }
}

/* getch：取一个字符（可能是压回的字符） */
int getch(void) {
    return bufp > 0 ? buf[--bufp] : getchar();
}

/* ungetch：把字符压回到输入中 */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getword：从输入中读取下一个单词或字符 */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
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





