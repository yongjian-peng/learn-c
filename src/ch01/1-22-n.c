#include <stdio.h>

#define TABSIZE 8
#define N 10 // line feed for every N characters

void printLine(char s[], int len)
{
    int counter;
    s[len] = '\n';
    s[len + 1] = '\0';
    printf("%s", s);
    for (counter = 0; counter < N + 1; counter++)
        s[counter] = '\0';
}

int main()
{
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
            printLine(line, j - 1); /* print and reset          */
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
            tempchar = getchar(); /* get the next char        */
            pos++;
            if (tempchar == EOF) /* end of the input         */
                break;
            else if (tempchar == '\n')
            {
                printLine(line, j); /* print and ignore \n    */
                j = 0;
                currentLen = 0;
                pos = 0;
                continue;
            }
            else if (tempchar == ' ')
            {
                printLine(line, j); /* print and save the blank in the next line  */
                j = 0;
                line[j++] = tempchar;
                currentLen = 1;
            }
            else if (tempchar == '\t')
            {
                printLine(line, j); /* print and save the Tab in the next line    */
                j = 0;
                line[j++] = tempchar;
                currentLen = TABSIZE; /* update the len of the line               */
                pos = pos + TABSIZE - (pos - 1) % TABSIZE - 1;
            }
            else /* next char is normal char                    */
            {
                if (c == ' ' || c == '\t')
                {
                    printLine(line, j); /* ' ' or \t at the end of the line        */
                    j = 0;
                    line[j++] = tempchar;
                    currentLen = 1;
                }
                else /* current char is normal char            */
                {
                    for (spacePos = 0; spacePos < j; spacePos++) /* find the last blank or Tab in the line     */
                    {
                        if (line[j - spacePos - 1] == ' ' || line[j - spacePos - 1] == '\t')
                            break;
                    }
                    // printf("spacePos is %d\n", spacePos);
                    if (spacePos == j) /* space or Tab is not found                  */
                    {
                        printLine(line, j);
                        j = 0;
                        line[j++] = tempchar;
                        currentLen = 1;
                    }
                    else /* space or Tab is found                       */
                    {
                        for (counter = 0; counter < spacePos; counter++)
                        {
                            wordchar[counter] = line[j - spacePos + counter]; /* save the part of the word at line end    */
                        }
                        printLine(line, j - spacePos);
                        for (counter = 0; counter < spacePos; counter++) /* save the last part in the next line      */
                            line[counter] = wordchar[counter];
                        j = spacePos;
                        line[j++] = tempchar;
                        currentLen = j;      /* update the length of the line            */
                        if (currentLen == N) /* maybe reach to N with the next char      */
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
    if (currentLen > 0) /* without \n at the end of the line    */
        printLine(line, j);

    return 0;
}