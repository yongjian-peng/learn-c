#include <stdio.h>

void enter_string(char str[]);
void delete_string(char str[], char ch);
void print_string(char str[]);

int main(void) {
    char c, str[50];
    enter_string(str);
    printf("The char to be delete is: ");
    scanf("%c", &c);
    delete_string(str, c);
    print_string(str);
    return 0;
}
