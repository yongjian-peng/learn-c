#include <stdio.h>
#include <ctype.h>
/* 
   编写函数expand(s1, s2),将字符串s1中类似a~z一类的速记符号
   在字符串s2中扩展为等价的完整列表abc...xyz.该函数可以处理大小写字母和数字
   并可以处理 a-b-c a-z0-9与-a-z等类似的情况，作为前导和尾随的-字符原样排印 
 */
void expand(char s1[], char s2[]);
int main()
{
    char s1[] = "-a-c, e-c-a, a-a, a-Z, a-9\n-A-C, E-C-a, A-A, A-z, A-9\n-0-2, 4-2-0, 0-0, 0-z, 0-Z\n";
    char s2[1000];
    expand(s1, s2);
    printf("source string:\n%s\n result string:\n%s\n", s1, s2);
    return 0;
}
void expand(char s1[], char s2[]) {
    char c;
    int i = 0;
    int j = 0;
    while ((c = s1[i]) != '\0') {
        char nextc = s1[i + 1];
        if (nextc == '-') {
            char thirdc = s1[i + 2];
            if (
                isdigit(c) && isdigit(thirdc) ||
                isupper(c) && isupper(thirdc) ||
                islower(c) && islower(thirdc)
            ) {
                if (c < thirdc) {
                    while(c <= thirdc) {
                        s2[j++] = c;
                        c++;
                    }
                } else {
                    while(c >= thirdc) {
                        s2[j++] = c;
                        c--;
                    }
                }
                i += 3;
            } else {
                s2[j++] = s1[i++];
            }
        } else {
            s2[j++] = s1[i++];
        }
    }
    s2[j] = '\0';
}