#include <stdio.h>
int main()
{
    int i, j;
    for (j = 1; j <= 9; j++)
    {
        for (i = 1; i <= j; i++)
        {
            printf("%d*%d=%-4d", i, j, i * j);
        }
        printf("\n");
    }
    return 0;
}