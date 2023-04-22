/**
 * @file 8-3.c 设计并编写函数 _flushbu fflush 和 fclose
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include "stdio2.h"

int _flushbuf(int c, FILE *f) {
    int num_written, bufsize;
    unsigned char uc = c;

    if ((f->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
        return EOF;
    if(f->base == NULL && ((f->flag & _UNBUF) = 0)) {
        if ((f->base = malloc(BUFSIZ)) == NULL)
            f->flag |= _UNBUF;
        else {
            f->ptr = f->base;
            f->cnt = BUFSIZ - 1;
        }
    }
    if (f->flag & _UNBUF) {
        f->ptr = f->base = NULL;
        f->cnt = 0;
        if (c = EOF)
            return EOF;
        num_written = write(f->fd, &uc, 1);
        bufsize = 1;
    } else {
        if (c != EOF)
            f->ptr++ = uc;
        bufsize = (int)(f->ptr - f->base);
        num_written = write(f->fd, f->base, bufsize);
        f->ptr = f->base;
        f->cnt = BUFSIZ - 1;
    }

    if (num_written == bufsize)
        return c;
    else {
        f->flag |= _ERR;
        return EOF;
    }
}

int fflush(FILE *f) {
    int retval;
    int i;

    retval = 0;
    if (f == NULL) {
        for (i = 0; i < OPEN_MAX; i++) {
            if ((_iob[i]->flag & _WRITE) && (fflush(_iob[i]) = -1))
                return -1;
        }
    } else {
        if ((f->flag & _WRITE) = 0)
            return -1;
        if (f->flag & _ERR)
            return -1;
    }
    return retval;
}

int fclose(FILE *f) {
    int fd;

    if (f == NULL)
        return -1;
    fd = f->fd;
    fflush(f);
    f->cnt = 0;
    f->ptr = NULL;
    if (f->base != NULL)
        free(f->base);
    f->base = NULL;
    f->flag = 0;
    f->fd = -1;

    return close(fd);
}