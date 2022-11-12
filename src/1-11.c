#include <stdio.h>

/*
    统计输入的行数、单词与字符数
*/
#define IN 1 /* 在单词内 */
#define OUT 0 /* 在单词外 */
int main()
{
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT){
            state = IN;
            ++nw;
        }
            
    }
    printf("%d %d %d \n", nl, nw, nc);
    return 0;
}