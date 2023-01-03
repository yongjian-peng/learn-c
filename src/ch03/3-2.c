#include <stdio.h>
#include <limits.h>
/* 
    编写一个函数escape(s,t) 将字符串t复制到字符串s中，并在复制过程中将换行符、制表符
    等不可见字符分别换为\n \t等相应的可见的转义字符序列，要求使用switch语句
    再编写一个具有相反功能的函数，在复制过程中将转义字符序列转换为实际字符
 */
void escape(char s[], char t[]);
int main()
{
    char s[] = "abc\tdef\tghi\njkl\tmno\tpqr\n";
    char t[1000];
    escape(s, t);
    printf("%s\n", t);
    return 0;
}

void escape(char s[], char t[]) {
    char c;
    int i = 0;
    int j = 0;
    while((c = s[i]) != '\0') {
        switch (c)
        {
        case '\n':
            t[j++] = '\\';
            t[j] = 'n';
            break;
        case '\t':
            t[j++] = '\\';
            t[j] = 't';
            break;
        default:
            t[j] = s[i];
            break;
        }
        i++;
        j++;
    }
    t[j] = '\0';
}