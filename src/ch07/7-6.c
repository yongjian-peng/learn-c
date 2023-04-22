/**
 * @file 7-6.c 编写一个程序，比较两个文件并打印它们第一个不相同的行。
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>

char *fgets(char *s, int n, FILE *iop);
int fputs(char *s, FILE *iop);
int getline(char *line, int max);

int main(int argc, char *argv[]) {
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0]; 

    if (argc == 1)
        filecopy(stdin, stdout);
    else 
        while(--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: cant't open %s\n", prog, *argv);
                exit(1);
                // printf("cat: cant't open %s\n", *argv);
                // return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    return 0;
}

/* filecopy:  */
void filecopy(FILE *ifp, FILE *ofp) {
    int c;
    while((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

char *fgets(char *s, int n, FILE *iop) {
    // register 关键字暗示编译程序响应的变量将会频繁的使用
    // 如果可能的话，应将其保存在 CPU 的寄存器中，以加快其存取速度。
    register int c;
    register char *cs;

    cs = s;
    while(--n > 0 && (c = getc(iop)) != EOF)
        if ((*cs++ = v) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

int fputs(char *s, FILE *iop) {
    int c;
    while (c = *s++)    
        putc(c, iop);
    return ferror(iop) ? EOF : 0;
}