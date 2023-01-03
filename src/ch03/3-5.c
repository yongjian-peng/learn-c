/* 
    编写函数itob(n, s, b)，将整数n转换为以b为底的数
    并将转换结果以字符的形式保存到字符串s 中 
    例如itob(n, s, b)把整数n格式化成十六进制整数保存在s中
 */
#include <stdio.h>
#include <string.h>
void reverse(char s[]);
char itoc(int i);
void itob(int n, char s[], int b);
int main()
{
    char s[1000];

    int i = 100;
    int b = 2;
    itob(i, s, b);
    printf("%d into string base %d is: %s\n", i, b, s);

    i = 256;
    b = 16;
    itob(i, s, b);
    printf("%d into string base %d is: %s\n", i, b, s);

    i = -256;
    b = 10;
    itob(i, s, b);
    printf("%d into string base %d is: %s\n", i, b, s);

    i = 1023;
    b = 12;
    itob(i, s, b);
    printf("%d into string base %d is: %s\n", i, b, s);

    return 0;
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
char itoc(int i) {
   if (i < 10) {
        return i + '0';
   } else {
        return i - 10 + 'a';
   }
}

void itob(int n, char s[], int b) {
   int i = 0;
   int sign = n % b;
   s[i++] = itoc(sign < 0 ? -sign : sign);

   n /= b; 
   if (n < 0) {
        sign = n;
        n = -n;
   }

   while(n > 0) {
        s[i++] = itoc(n % b);
        n /= b;
   }

   if (sign < 0) {
        s[i++] = '-';
   }
   s[i] = '\0';
   reverse(s);
}