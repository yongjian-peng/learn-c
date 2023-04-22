/**
 * @file get.c 将从文件的任意位置读入任意数目的字节，它返回读入的字节数，若发生错误，则返回-1
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

int get(int fd, long pos, char *buf, int n);

int get(int fd, long pos, char *buf, int n) {
    // lseek 系统调用返回一个long类型的值，此值表示文件的新位置，若发生错误，则返回-1
    // 标准库函数 fseek 与系统调用 lseek 类似，所不同的是，前者的第一个参数是 FILE*类型
    // 且在发生错误时返回一个非0值。
    if (lseek(fd, pos, 0) > = 0)
        return read(fd, buf, n);
    else 
        return -1;
}