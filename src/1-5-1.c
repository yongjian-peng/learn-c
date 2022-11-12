#include <stdio.h>

int main() {
    // int c;
    // while((c = getchar()) != EOF) {
    //     putchar(c);
    // }
    // long nc;
    // nc = 0;
    // while(getchar() != EOF) {
    //     ++nc;
    // }
    // printf("%ld\n", nc);

    // double nc;
    // for (nc = 0; getchar() != EOF; ++nc){
    //     printf("getchar\n");
    // }

    // printf("%.1f\n", nc);

    // 统计输入的行数
    int c, nl;
    nl = 0;
    while((c = getchar()) != EOF) {
        if (c == '\n')
            ++nl;
    }
    printf("%d\n", nl);
    return 0;
}