/**
 * @file myprog.c 命令行参数例子：
 * 演示了如何使用命令行参数来控制程序的行为， 假设我们的程序名为 myprog 它能接受两个命令行参数
 * -f filename 表示要处理的文件名
 * -o outputfile 表示输出结果的文件名
 * myprog -f input.txt -o output.txt
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *filename = NULL;
    char *outputfile = NULL;

    // 处理命令行参数
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            filename = argv[++i];
        } else if (strcmp(argv[i],"-o") == 0 && i + 1 < argc) {
            outputfile = argv[++i];
        } else {
            printf("Usage: %s -f filename -o outputfile \n", argv[0]);
            return 1;
        }
    }

    if (filename == NULL || outputfile == NULL) {
        printf("Usage: %s -f filename -o outputfile\n", argv[0]);
        return 1;
    }

    // 打开文件进行处理
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open %s\n", filename);
        return 1;
    }
    // 处理文件，并将结果输出到指定的文件
    FILE *outfp = fopen(outputfile, "w");
    if (outfp == NULL) {
        printf("Failed to open file %s\n", outputfile);
        fclose(fp);
        return 1;
    }

    fclose(fp);
    fclose(outfp);

    return 0;
}
