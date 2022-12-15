#include <stdio.h>
#include <limits.h>
/* 
    shellsort 函数，按递增顺序对v[0] v[n-1]进行排序 
    并打印数组
 */
void shellsort(int v[], int n);
void printi(int (*arr)[], int sz);
int main()
{
    int a[5] = {1, 3, 4, 2, 5};

    int sz = sizeof(a) / sizeof(a[0]);

    shellsort(a, sz);
    printi(&a, sz);
    return 0;
}

void shellsort(int v[], int n) {
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j-=gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
}

void printi(int (* arr)[], int sz) {
    int i = 0;
    for (i = 0; i < sz; i++) {
        printf("%d ", (*arr)[i]);
    }
    printf("\n");
}