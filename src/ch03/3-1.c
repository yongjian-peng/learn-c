#include <stdio.h>
#include <limits.h>
/* 
    练习在上面折半查找的例子中，while 循环语句内共执行了两次测试，
    其实只要一次就足够（代价是将更多的测试在循环外执行）。
    重写改函数，使得在循环内部只执行一次测试，比价两种版本函数的运行时间。
 */
int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);
#define MAX 10000 // 数组的长度
int main() {
    int v[MAX];
    int i, x, n;

    for (i = 0; i < MAX; i++)
        v[i] = i;

    x = 1010000;
    n = binsearch(x, v, MAX);
    printf("%d\n", n);

    n = binsearch2(x, v, MAX);
    printf("%d\n", n);
    return 0;
}

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while(low <= high) {
        mid = (low + high) >> 1;
        if (x < v[mid])
            high = mid - 1;
        else if(x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binsearch2(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (v[mid = (low + high) >> 1] != x && low != high) {
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
    }
    if (v[mid] == x)
        return mid;
    else
        return -1;
}