#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;
    return (*pa - *pb);
}

int cmp(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}

int main()
{
    int arr[] = {5, 2, 8, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(int), compare);

    // 输出排序后的数组
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    char str[] = "cbafed";
    int s = strlen(str);

    qsort(str, s, sizeof(char), cmp);

    printf("%s\n", str);
    return 0;
}