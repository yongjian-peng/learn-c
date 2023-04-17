#include <stdio.h>
#include <string.h>
#include <ctype.h>
/**
 * @brief  修改 undcl 程序 使它把文字描述转换为声明过程中不会生成多余的圆括号
 * @note   
 * @retval None
 * x int
    int x
argv * * char
    char (*(*argv))
daytab * [13] int
    int (*daytab)[13]
daytab [13] * int
    int (*daytab[13])
comp () * void
    void (*comp())
comp * () void
    void (*comp)()
x () * [] * () char
    char (*(*x())[])()
x [3] * () * [5] char
    char (*(*x[3])())[5]
 */
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

#define BUFSIZE 100

int tokentype;//最后一次输入的符号类型
char token[MAXTOKEN];//最后一个符号字符串
char name[MAXTOKEN];//标识符名
char datatype[MAXTOKEN];//数据类型，包括char、int等
char out[1000];
char buf[BUFSIZE];
int bufp = 0;

int gettoken(void);

int getch(void);
void ungetch(int c);

int main(void)
{
	int type;
	char temp[MAXTOKEN];

	while(gettoken() != EOF) {
		strcpy(out, token);
		while((type = gettoken()) != '\n') {
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				sprintf(temp, "(*%s)", out);
				strcpy(out, temp);
			}
			else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else	
				printf("invalid input at %s \n", token);
		}
		printf("%s\n", out);
	}
    return 0;
}

/* gettoken：返回下一个记号 */
int gettoken(void) {
    int c;
	char *p = token;

	while((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
			ungetch(c);
			return tokentype = '(';
	}
	else if (c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}


/* getch：取一个字符（可能是压回的字符） */
int getch(void) {
    return bufp > 0 ? buf[--bufp] : getchar();
}

/* ungetch：把字符压回到输入中 */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
