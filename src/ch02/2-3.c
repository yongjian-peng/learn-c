#include <stdio.h>
#include <string.h>
/* 编写函数htoi(s) 把由十六进制数字组成的字符串（包含可选的前缀
    0x或0X）转换为与之等价的整型值，字符串中允许包含的数字包括：0-9 a~f以及A~F */
int htoi(char s[]);
int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (argc != 2) {
            printf("Warn: too many args.");
        }
        printf("%d\n", htoi(argv[1]));
    } else {
        char s[] = "0xaa";
        printf(
            "Info: not specifed hexadecimal digits, will use default value: %s.\n",
             s);
        printf("%d\n", htoi(s));
    }
}

int htoi(char s[]) {
    int rt = 0;
    int start = 0;

    if (strlen(s) > 2) {
        char first = s[0];
        char second = s[1];
        if (first == '0' && (second == 'x' || second == 'X')) {
            start = 2;
        }
    }
    int i;
    char c;
    for (i = start; (c = s[i]) != '\0'; i++) {
        int v;
        if ('0' <= c && c <= '9') {
            v = c - '0';
        } else if('a' <= c && c <= 'f') {
            v = 10 + c - 'a';
        } else if ('A' <= c && c <= 'F') {
            v = 10 + c - 'A';
        } else {
            printf("Error: Illegal hexadecimal digits: %s\n", s);
            return 0;
        }
        rt = rt * 16 + v;
    }
    return rt;
}
