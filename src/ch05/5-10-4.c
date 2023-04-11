#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXCHAR 1000
#define MAXSTACK 100

int sp = 0;
int stack[MAXSTACK];

int atoi(char s[]);
int pop(void);
void push(int c);

int main(int argc, char *argv[]) {

    // while(--argc >= 0) {
    //     printf("agrc:%d, argv[agrc-1]%s\n", argc, argv[argc]);
    // }

    int c, op2, type, number, i;

    // printf("----------\n");
    // printf("Note: This simplified calculator can only take in '+' , '-',\n");
    // printf("(multiple), '/', and inter number~\n");
    // printf("------------\n");

    while (--argc > 0) {
        printf("agrc:%d\n", argc);
        c = (*++argv)[0];
        printf("%c\n", c);
        if (c >= '0' && c <= '9') {
            for (i = 0; c >= '0' && c <= '9'; i++)
                c = *(*argv + i);
            if (c == '\0'){
                number = atoi(*argv);
                c = NUMBER;
            }
        }
        switch (c)
        {
        case NUMBER:
            push(number);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '`':
            push(pop() * pop());
            break;
        case '/':
            if (0 == (op2 = pop())){
                printf("Error: '0' cannot be divided.\n");
                return 0;
            }
            push(pop() / op2);
            break;
        default:
            break;
        }
    }
    printf("Answer is: %d\n", pop());
    return 1;
}

int pop(void) {
    if (sp <= 0) {
        printf("return: no value remain in stack.\n");
        return 0;
    }
    else 
        return stack[--sp];
}

void push(int op) {
    if (sp >= MAXSTACK) {
        printf("return stack has not enough space.\n");
        return;
    }
    else 
        stack[sp++] = op;
    return;
} 

int atoi(char s[])
{
    int i, sign, val;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0; isdigit(s[i]); i++)
        val = 10 * val + (s[i] - '0');
    return sign * val;
}