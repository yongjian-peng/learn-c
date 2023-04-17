/**
 * @file 5-18.c 修改dcl 程序 使它能处理输入中的错误
 * 扩展dcl 程序的功能，使它能够处理包含其他成分的声明，
 * 例如带有函数参数类型的声明、带有类似于const限定符的声明等。
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-13
 * 
 * @copyright Copyright (c) 2023
 * command gcc -o ./5-18.exe .\5-18.c lexer.c parser.c getch.c
 * .\5-18.exe
 * char (*(*x[3])())[5]
 */

#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

char datatype[MAXTOKEN]; /* 数据类型（char int等） */
char out[1000]; /* 输出字符串 */

/* dcl 将声明转换为文字描述 */
int main()
{
    while(gettoken() != EOF) { /* 该行的第一个记号是数据类型 */
        strcpy(datatype, token);
        out[0] = '\0';
        dcl(); /* 分析该行的其余部分 */
        if(tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}