/**
 * @file copyfile.c 将一个文件复制到另一个文件，我们编写的这个版本仅仅只能复制一个文件
 * 不允许用目录作为第二个参数，并且目标文件的权限不是通过复制获得的，而是重新定义的
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-22
 * command  .\copyfile.exe .\copyfile.c ./copy.c 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <stdarg.h>

#define PERMS 0666

void error(char *, ...);
int main(int argc, char *argv[]) {
    int f1, f2, n;

    char buf[BUFSIZ];

    if (argc != 3)
        error("Usage: cp from to");
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
        error("cp: cant't open %s", argv[1]);
    if ((f2 = creat(argv[2], PERMS)) == -1)
        error("cp: cant't create %s, mode %03o", argv[2], PERMS);
    while((n = read(f1, buf, BUFSIZ)) > 0)
        if (write(f2, buf, n) != n)
            error("cp: write error on file %s", argv[2]);
    return 0; 
}

void error(char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vprintf(fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}