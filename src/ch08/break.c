#include <stdio.h>

int main(int argc, char *argv[]) {
    int num = 1;
    while(num < 100) {
        num *= 2;
    }
    printf("num=%d", num);
    return 0;
}