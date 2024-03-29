/**
 * @file 7-7.c 修改第5章的模式查找程序，使它从一个命名文件的集合中读取输入（有文件名参数）
 * 如果没有文件名参数，则从标准输入中读取输入，当发现一个匹配行时， 是否应该将响应的文件名打印出来？
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000 /* 最大输入行长度 */

int find_in_file(FILE *fp, char *filename, char *pattern, int except, int number);

/* find: 打印所有与第一个参数指定的模式匹配的行，支持选项参数，可用参数指定一组文件名 */
int main(int argc, char *argv[]) {
    char *pattern;
    FILE *fp;
    int c, except = 0, number = 0, found = 0;

    /* 解析命令行参数 */
    while(--argc > 0 && (*++argv)[0] == '-')
        while(c = *++argv[0])
            switch(c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    return -1;
            }
    if (argc < 1) {
        printf("Usage: find -x -n pattern [file...]\n");
        return 0;
    }

    pattern = *argv;
    if (argc == 1) /* 未指定文件名，从标准输入读取 */
        found = find_in_file(stdin, NULL, pattern, except, number);
    else
        while(--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("find: cant't open %s\n", *argv);
                return -1;
            }
            found += find_in_file(fp, *argv, pattern, except, number);
            fclose(fp);
        }
    return found;
}

/* find_in_file: 打印指定文件中与pattern匹配的行，返回匹配的行数 */
int find_in_file(FILE *fp, char *filename, char *pattern, int except, int number) {
    char line[MAXLINE];
    long lineno = 0, found = 0;

    if (filename)
        printf("\n%s:\n", filename);
    while(fgets(line, MAXLINE, fp)) {
        ++lineno;
        if ((strstr(line, pattern) != NULL) != except) {
            if (number)
                printf("%ld:", lineno);
            printf("%s",line);\
            ++found;
        }
    }
    return found;
}