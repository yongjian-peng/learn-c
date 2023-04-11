#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define TABSTOP 8   // 默认制表符停止位宽度

void entab(int m, int n);
void detab(int m, int n);
int getline(char s[], int lim);

int main(int argc, char *argv[]) {
    int m = 0;
    int n = TABSTOP;

    // 解析命令行参数
    while (--argc > 0 && (*++argv)[0] == '-') {
        switch ((*argv)[1]) {
            case 'm':
                m = atoi(++(*argv));
                break;
            case 'n':
                n = atoi(++(*argv));
                break;
            default:
                printf("error: unsupported option %s\n", *argv);
                return 1;
        }
    }

    if (argc > 0 && (*argv)[0] == 'e') {
        entab(m, n);
    } else if (argc > 0 && (*argv)[0] == 'd') {
        detab(m, n);
    } else {
        printf("usage: %s [-m tab_start][-n tab_stop] [e|d]\n", argv[0]);
        printf("e: entab\n");
        printf("d: detab\n");
        return 1;
    }

    return 0;
}

// entab: replace strings of blanks with tabs and blanks
void entab(int m, int n) {
    char line[MAXLINE];
    int pos, spaces, tabs, i, j;

    while (getline(line, MAXLINE) > 0) {
        pos = spaces = tabs = 0;

        for (i = 0; line[i] != '\0'; ++i) {
            if (line[i] == ' ') {
                if (pos + 1 == m) {
                    tabs = 0;
                    spaces = 1;
                } else if (pos >= m && (pos - m + 1) % n == 0) {
                    ++tabs;
                    spaces = 0;
                } else {
                    ++spaces;
                }
            } else {
                for (j = 0; j < tabs; ++j) {
                    putchar('\t');
                }

                if (spaces > 0) {
                    for (j = 0; j < spaces; ++j) {
                        putchar(' ');
                    }
                }

                putchar(line[i]);
                ++pos;

                if (line[i] == '\t') {
                    pos += TABSTOP - (pos - 1) % TABSTOP - 1;
                }

                if (pos == m) {
                    tabs = spaces = 0;
                } else if (pos > m && (pos - m) % n == 0) {
                    tabs = 1;
                    spaces = 0;
                } else {
                    tabs = spaces = 0;
                }
            }
        }
    }
}

// detab: replace tab characters with proper number of blanks
void detab(int m, int n) {
    char line[MAXLINE];
    int pos, i, j;

    while (getline(line, MAXLINE) > 0) {
        pos = 0;

        for (i = 0; line[i] != '\0'; ++i) {
            if (line[i] == '\t') {
                for (j = pos + 1; j < m || (j - m + 1) % n != 0; ++j) {
                    putchar(' ');
                }

                pos = j - 1;
            } else {
                putchar(line[i]);
                ++pos;

                if (line[i] == '\n') {
                    pos = 0;
                }
            }
        }
    }
}

// getline: read a line into s, return length
int getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}