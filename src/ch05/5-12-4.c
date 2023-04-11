#include <stdio.h>

#define MAX 15

int main() {
    // int a, b;

    // printf("Enter first number: ");
    // scanf("%d", &a);

    // printf("Enter second number: ");
    // scanf("%d", &b);

    // printf("A: %d \t B: %d\n", a, b);

    char buf[MAX];

    // fgets(buf, MAX, stdin);
    // printf("string is：%s\n", buf);
    // printf("Enter a string: ");
    // gets(buf);
    // printf("string is: %s\n", buf);

    // 定义指针数组
    int x = 20, y = 30;
    int *z[3] = {&x, &y};

    printf("%d\n", *(*(z+0)));

    int arr[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    // 定义数组指针
    int (*p)[3] = arr;

    printf("%d\n", *(*(p+1)+0));
    printf("%d\n", *(*(p+1)+1));



    return 0;
}