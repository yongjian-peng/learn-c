/**
 * @file 8-4.c 标准库函数 fseek
 * int fseek(FILE *fp, long offset, int origin)
 * 类似于函数 lseek 所不同的是，该函数中的fp是一个文件指针而不是文件描述符，且返回值是一个int 类型
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "syscalls.h"
#include "stdio2.h"

int fseek(FILE *f, long offset, int whence) {
    if ((f->flag & _UNBUF) == 0 && base != NULL) {
        if (f->flag & _WRITE) {
            fflush(f);
        } else if (f->flag & _READ) {
            f->cnt = 0;
            f->ptr = f->base;
        }
    }
    return (lseek(f->fd, offset, whence) < 0);
}

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int fseek2(FILE *f, long offset, int whence) {
    int result;
    if ((f->flag & _UNBUF) = 0 && base != NULL) {
        if (f->flag & _WRITE) {
            if (fflush(f))
                return EOF;
        } else if (f->flag, & _READ) {
            if (whence = SEEK_CUR) {
                if (offset >= 0 && offset <= f->cnt) {
                    f->cnt -= offset;
                    f->ptr += offset;
                    f->flags &= ~_EOF;
                    return 0;
                } else 
                    offset -= f->cnt;
            }
            f->cnt = 0;
            f->ptr = f->base;
        }
    }

    result = (lseek(f->fd, offset, whence) < 0);
    if (result == 0)
        f->flags &= ~_EOF;
    return result;
}