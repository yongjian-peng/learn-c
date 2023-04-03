#include <stdio.h>
#define PPP printf("what does it for?\n");

int* daytab[2];
int a[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int b[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int day_of_year(int year, int month, int day)
{
    int i, leap;
    if (year < 1) {
        return -1;
    }
    if (month > 12 || month < 1)
        return -1;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (day < 0 || day > daytab[leap][month]) {
        printf("Error: invalid day input\n");
        return -1;
    }
    for (i = 1; i < month; i++)
    {
        day += daytab[leap][i];
        printf("dattab:[%d][%d]:%d\n", leap, i, daytab[leap][i]);
    }
    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    if (year < 0)
        return -1;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (yearday < 1 || yearday > 365 + leap)
    {
        printf("Error: invalid year day input\n");
        return -1;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
    return 1;
}

int main() {
    // int* a[2];
    // int m[] = {8, 99, 109};
    // int n[] = {11, 33, 44, 66};
    // a[0] = m;
    // a[1] = n;
    // printf("a[1]:%d\n", a[1][1]);
    int choice;
    int year, month, day, day_of_month, yearday, ret;
    int pmonth, pday;
    daytab[0] = a;
    daytab[1] = b;

    printf("%d\n", daytab[1][2]);
    printf("This program is intended to display day of the year,\n"
			"or the exact month and day of the year.\n"
			"Choose '1': Input year, month, day of the month,\n"
			"and it'll automatically show the day of year.\n"
			"Choose '2': Input day_of_year, and it'll display\n"
			"month and day_of_month.\n");
	printf("input function choice:\n");
	printf("1. day of year\n2. month and day of month\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("year: \n");
        scanf("%d", &year);
        printf("month:\n");
        scanf("%d", &month);
        printf("day\n");
        scanf("%d", &day);
        ret = day_of_year(year, month, day);
        if (ret == -1)
            break;
        printf("The day of year is: %d\n", ret);
        break;
    case 2:
        printf("Input the year:\n");
        scanf("%d", &year);
        printf("The day of year:\n");
        scanf("%d", &yearday);
        ret = month_day(year, yearday, &pmonth, &pday);
        if (ret == -1)
            break;
        printf("month and day: %d.%d\n", pmonth, pday);
        break;
    default:
        printf("Unknown instruction, program exits..\n");
        break;
    }
    return 1;
}

