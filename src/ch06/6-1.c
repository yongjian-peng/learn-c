#include <stdio.h>
#include <ctype.h>
#include <string.h>
/**
 * @brief  上述getword 函数不能正确处理下划线、字符串常量、注释及预处理器控制指令。请编写一个更完善的 getword 函数
 * @note   
 * @param  sizeof(keytab[0]: 
 * @retval 
 * command auto auto
 */
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))
// #define NKEYS (sizeof keytab / sizeof(struct key))

int getword(char *word, int lim);

struct  key 
{
    char *word;
    int count;
};

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

int binsearch(char *word, struct key tab[], int n);

int main() {
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for(n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* binsearch : find word in tab[0] .. tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else    
            return mid;
    }
    return -1;
}

int getch(void);
void ungetch(int c);

/* getword: 从输入中读取下一个单词或字符 */
int getword(char *word, int lim)
{
    int c;
    char *w = word;
    // isspace 函数跳过空白符
    // isalpha 函数识别字母
    // isalnum 函数识别字母和数字 这些函数定义在 <ctype.h> 中
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
    if (bufp > BUFSIZ)
        printf("ungetch: too many characters\n");
    else    
        buf[bufp++] = c;
}