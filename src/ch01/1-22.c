#include <stdio.h>

/* 编写一个程序，把较长的输入行 “折” 成短一些的两行或者多行，折行的位置
    在输入行的第n列之前的最后一个非空格之后，要保证程序能够智能地处理输入
    行很长以及在指定的列前没有空格或制表符时的情况
 */
#define TABSIZE 8
#define N 10 // line feed for every N characters 每N个字符换行

void printLine(char s[], int len) {
    int counter;
    s[len] = '\n';
    s[len + 1] = '\0';
    printf("%s", s);
    for (counter = 0; counter < N + 1; counter++)
        s[counter] = '\0';
}

int main() {
    int c, tempchar;
    int pos;
    char line[N + 2] = {'\0'};
    int currentLen = 0;
    int j = 0;
    int spacePos;
    int counter;
    char wordchar[N] = {'\0'};
    for (pos = 1; (c = getchar()) != EOF; pos++)
    {
        line[j++] = c;
        currentLen++;
        if (c == '\n')
        {
            printLine(line, j - 1);
            j = 0;
            currentLen = 0;
            pos = 0;
            continue;
        } 
        else if (c == '\t')
        {
            currentLen = currentLen + TABSIZE - (pos - 1) % TABSIZE - 1;
            pos = pos + TABSIZE - (pos - 1) % TABSIZE - 1;
        }

        if (currentLen >= N)
        {
            tempchar = getchar();
            pos++;
            if (tempchar == EOF)
                break;
            else if (tempchar == '\n')
            {
                printLine(line, j); /* 打印并忽略 \n */
                j = 0;
                currentLen = 0;
                pos = 0;
                continue;
            }
            else if (tempchar == ' ')
            {
                printLine(line, j); // 打印并将空白保存在下一行
                j = 0;
                line[j++] = tempchar;
                currentLen = 1;
            } 
            else if (tempchar == '\t')
            {
                printLine(line, j); // 打印并保存下一行中的选项卡
                j = 0;
                line[j++] = tempchar;
                currentLen = TABSIZE; // 更新行的长度
                pos = pos + TABSIZE - (pos - 1) % TABSIZE - 1;
            }
            else 
            {
                if (c == ' ' || c == '\t')
                {
                    printLine(line, j); // ' ' 或者 \t 在行的末尾
                    j = 0;
                    line[j++] = tempchar;
                    currentLen = 1;
                }
                else // 当前字符是普通字符
                {
                    // 当前字符是普通字符查找行中的最后一个空白或 tab
                    for (spacePos = 0; spacePos < j; spacePos++)
                    {
                        if(line[j - spacePos - 1] == ' ' || line[j - spacePos - 1] == '\t')
                            break;
                    }
                    if (spacePos == j)
                    {
                        printLine(line, j);
                        j = 0;
                        line[j++] = tempchar;
                        currentLen = 1;
                    }
                    else 
                    {
                        for (counter = 0; counter < spacePos; counter++)
                        {
                            // 将单词的一部分保存在行尾
                            wordchar[counter] = line[j - spacePos + counter]; 
                        }
                        printLine(line, j - spacePos);
                        for (counter = 0; counter < spacePos; counter++)
                            line[counter] = wordchar[counter];
                        j = spacePos;
                        line[j++] = tempchar;
                        currentLen = j;
                        if (currentLen == N)
                        {
                            printLine(line, j);
                            j = 0;
                            currentLen = 0;
                        }
                    }
                }
            }
        }
    }
    if (currentLen > 0)
        printLine(line, j);
    return 0;
}