/**
 * @file 8-2.c 用字段代替显示的按位操作，重写 fopen 和 _fillbuf 函数 比较响应代码的长度和执行速度
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <fcntl.h>
#include "stdio2.h"

#define PERMS 0666

FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        
}