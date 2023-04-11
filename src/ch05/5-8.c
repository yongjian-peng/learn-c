#include <stdio.h>
/* 函数day_of_year 和 month_day 中没有进行错误检查，请解决改问题 */

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    int month, day;
    month = 2;
    day = 29;
    month_day(1988, 60, &month, &day);

    printf("%d\n", month);
    printf("%d\n", day);

    day = day_of_year(2023, 4, 26);

    printf("%d\n", day);


    return 0;
}

int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = year %4 == 0 && year %100 != 0 || year % 400 == 0;
    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > daytab[leap][month])
        return -1;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (year < 1)
    {
        *pmonth = -1;
        *pday = -1;
        return;
    }

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    if (i > 12 && yearday > daytab[leap][12])
    {
        *pmonth = -1;
        *pday = -1;
    } 
    else
    {
        *pmonth = i;
        *pday = yearday;
    } 
    
}