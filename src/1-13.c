#include <stdio.h>
#include <ctype.h>

/* 打印输入中单词长度的直方图，水平方向的直方图比较容易绘制，垂直方向的直方图则要困难些 */
void updatecounts(int counts[], int len, int wordlen);
int getpeak(int counts[], int len);
void painth(int counts[], int len);
void paintv(int counts[], int len);

int main() {
    int len = 10;
    int counts[len];
    int i;
    for (i = 0; i < len; counts[i++] = 0)
        ;
    int isIn = 0;
    int wordlen = 0;
    char c;
    while ((c = getchar()) != EOF)
    {
        if (isIn) {
            if (isspace(c)) {
                updatecounts(counts, len, wordlen);
                isIn = 0;
                wordlen = 0;
            } else {
                wordlen++;
            } 
        } else {
            if (!isspace(c)) {
                isIn = 1;
                wordlen = 1;
            }
        }
    }
    if (wordlen > 0)
        updatecounts(counts, len, wordlen);

    painth(counts, len);
    paintv(counts, len);
    return 0;
}

void updatecounts(int counts[], int len, int wordlen) {
    wordlen = wordlen < len ? wordlen : len;
    counts[wordlen - 1]++;
}

int getpeak(int counts[], int len) {
    int peak = 0;
    int i;
    for (i = 0; i < len; i++) {
        peak = peak > counts[i] ? peak : counts[i];
    }
    return peak;
}

void painth(int counts[], int len) {
    printf("\nHorizontal histogram:\n\n");
    int peak = getpeak(counts, len);
    int i;
    for (i = 0; i < len; i++) {
        int barlen = counts[i] * 20 / peak + 1;
        char bar[barlen];
        int j;
        for (j = 0; j < barlen - 1; j++) {
            bar[j] = '+';
        }
        bar[j] = '\0';

        char *format = " %2d: %s %d\n";
        if (i == len - 1) {
            format = ">=%2d: %s %d\n";
        }
        printf(format, i + 1, bar, counts[i]);
    }
}

void paintv(int counts[], int len) {
    printf("\nVertical Histogram:\n\n");
    int peak = getpeak(counts, len);
    int i, j, h = 20;

    int bars[len];
    for (i = 0; i < len; i++) {
        bars[i] = counts[i] * h / peak;
    }

    for (i = 0; i <= h; i++) {
        for (j = 0; j < len; j++) {
            if (h - i == bars[j]) {
                printf("%-5d", counts[j]);
            } else if (h - i < bars[j]) {
                printf("%-5c", '+');
            } else {
                printf("%-5c", ' ');
            }
        }
        printf("\n");
    }

    for (i = 0; i < len; i++) {
        printf("=====");
    }
    printf("\n");
    for (i = 0; i < len; i++) {
        char *format = "%-5d";
        if (i == len - 1) {
            format = ">=%-5d";
        }
        printf(format, i + 1);
    }
    printf("\n"); 
}