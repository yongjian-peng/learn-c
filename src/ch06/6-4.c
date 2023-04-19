/**
 * @file 6-4.c 编写一个程序，根据单词的出现频率，降序打印输入中的各个不同的单词，并在每个单词前标上出现次数
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* 树的节点 */
struct tnode {
    char *word; /* 指向单词的指针 */
    int count;  /* 出现次数 */
    struct tnode *left;  /* 左子节点 */
    struct tnode *right; /* 右子节点 */
};

struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
struct tnode *talloc(void);

int getch(void);
void ungetch(int c);

int getword(char *word, int lim);

char *strdup_(char *s);

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

#define MAXWORD 100
struct tnode *add_fred_tree(struct tnode *freq_tree, struct tnode *node);
void inorder_word_tree(struct tnode *word_tree, struct tnode **freq_tree);

/* 根据单词的出现频率降序打印输入中的单词 */
int main() {
    struct tnode *word_tree = NULL, *freq_tree = NULL;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            word_tree = addtree(word_tree, word);
    inorder_word_tree(word_tree, &freq_tree);
    treeprint(freq_tree);
    return 0;
}

/* add_fred_tree: 将node按频率降序插入freq_tree */
struct tnode *add_fred_tree(struct tnode *freq_tree, struct tnode *node) {
    if (freq_tree == NULL) {
        freq_tree = talloc();
        *freq_tree = *node;
        freq_tree->left = freq_tree->right = NULL;
    }
    else if (node->count > freq_tree->count)
        freq_tree->left = add_fred_tree(freq_tree->left, node);
    else
        freq_tree->right = add_fred_tree(freq_tree->right, node);
    return freq_tree;
}

/* inorder_word_tree: 中序遍历word_tree 并将节点插入freq_tree */
void inorder_word_tree(struct tnode *word_tree, struct tnode **freq_tree) {
    if (word_tree != NULL) {
        inorder_word_tree(word_tree->left, freq_tree);
        *freq_tree = add_fred_tree(*freq_tree, word_tree);
        inorder_word_tree(word_tree->right, freq_tree);
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

/* getword: 从输入中读取下一个单词或字符 */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while(isspace(c = getch()))
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

/* strdup_: 复制s到某个位置（下划线避免与<string.h>中的strdup冲突） */
char *strdup_(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* addtree: 在p或p的下方增加一个节点w */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc(); /* 创建一个新节点 */
        p->word = strdup_(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
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

/* talloc: 创建一个tnode */
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}
