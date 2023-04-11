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
    printf("%d\n", *(*(z+1)));

    int arr[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    // 定义数组指针
    // int (*p)[3] = arr;

    // printf("%d\n", *(*(p+1)+0));
    // printf("%d\n", *(*(p+1)+1));

    int a = 20;
    int *p = &a;

    int **q = &p; // q作为二级指针，它的指向对象是 int *
    // 一级指针里面保存的数据的地址，二级指针里面保存的是一级指针的地址

    printf("**q%p\n", &q);
    printf("*q%p\n", q);
    printf("*q%d\n", **q);

    // enum Color{RED, GREEN, BLUE};
    // enum Color light;

    // scanf("%d\n", &light);
    char ch;
    while((ch == getchar()) != -1) {
        printf("0x%x \n", ch);
        printf("0x%d \n", ch);
    }



    return 0;
}