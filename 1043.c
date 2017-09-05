/*********************************1043************************************
题目描述：
We now use the Gregorian style of dating in Russia. The leap years are years 
with number divisible by 4 but not divisible by 100, or divisible by 400.
For example, years 2004, 2180 and 2400 are leap. Years 2004, 2181 and 2300 
are not leap.
Your task is to write a program which will compute the day of week corresponding 
to a given date in the nearest past or in the future using today’s agreement 
about dating.
输入：
There is one single line contains the day number d, month name M and year number 
y(1000≤y≤3000). The month name is the corresponding English name starting from 
the capital letter.
输出：
Output a single line with the English name of the day of week corresponding to 
the date, starting from the capital letter. All other letters must be in lower case.
样例输入：
9 October 2001
14 October 2001
样例输出：
Tuesday
Sunday
提示：
Month and Week name in Input/Output:
January, February, March, April, May, June, July, August, September, October, 
November, December
Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define ISLEAP(x) (x%4==0&&x%100!=0 || x%400==0)?1:0

int buf[3001][13][32];

char monthname[13][10] = {
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

char weekname[7][10]={
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

int dayofmonth[13][2]={
    0,0,
    31,31,
    28,29,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31
};

struct Date{
    int day;
    int month;
    int year;
}tmp;

void nextday(struct Date* tmp){
    tmp->day++;
    if(tmp->day > dayofmonth[tmp->month][ISLEAP(tmp->year)]){
        tmp->day = 1;
        tmp->month++;
        if(tmp->month > 12){
            tmp->month = 1;
            tmp->year++;
        }
    }
}


int main(){
    int d, y;
    char m[10];
    int i, days;
    int cnt = 0;
    /*
    struct Date *p = (struct Date*)malloc(sizeof(struct Date));
    p->year = 0;
    p->month = 1;
    p->day = 1;
    while(p->year <= 3001){
        buf[p->year][p->month][p->day] = cnt++;
        nextday(p);
    }
    */
    
    //struct Date tmp;
    tmp.year = 0;
    tmp.month = 1;
    tmp.day = 1;
    while(tmp.year <=3001){
        buf[tmp.year][tmp.month][tmp.day] = cnt;
        nextday(&tmp);
        cnt++;
    }
    
    while(scanf("%d %s %d", &d, m, &y) != EOF){
        for(i=1; i<13; i++)
            if(strcmp(m, monthname[i]) == 0)
                break;
 
        days = buf[y][i][d] - buf[2017][9][5];
        days += 2;
        printf("%s\n", weekname[(days%7+7)%7]);
    }
    return 0;
}

/*************************************************************************
1.这题的纯c风格的程序（如上代码）在自己电脑上跑会runtime error，但是在oj上
可以通过，应该是电脑配置、环境等方面的原因
2.这道题中如何定义结构体，如果将结构体指针作为函数参数进行传递，值得学习。
如果tmp没有在Line 84定义的话，就在Line 115定义即可
下面的代码也是纯c的代码，只是结构体换成了typedef定义。

——————————————————————————————————————————————————————————————————————————
typedef struct、struct的用法在c和c++里有一些不同
在C中定义一个结构体类型要是用typedef:
typedef struct Student
{
    int a;
}Stu;
于是在声明变量的时候就可以这样声明：Stu stu1;
——————————————————————————————————————————————————————————————————————————
如果在c中没有用typedef定义结构体：
struct Student
{
    int a;
};
就必须用struct Student stu1;来声明
typedef方式中的的Stu实际上就是struct Student的别名。Stu与struct Student等价
——————————————————————————————————————————————————————————————————————————
另外如果在c中使用typedef来定义，也可以不写Student，如下所示：
typedef struct
{
    int a;
}Stu;
于是也不能struct Student stu1;了，必须是Stu stu1;
——————————————————————————————————————————————————————————————————————————
但在c++里很简单，直接
struct Student
{
int a;
};　　　　
于是就定义了结构体类型Student，声明变量时直接Student stu2；
——————————————————————————————————————————————————————————————————————————
struct   Student   
{   
    int   a;   
}stu1;//stu1是一个变量  

typedef   struct   Student2   
{   
    int   a;   
}stu2;//stu2是一个结构体类型=struct Student  

使用时可以直接访问 stu1.a
但是stu2则必须先 stu2 s2;
然后 s2.a=10;
——————————————————————————————————————————————————————————————————————————
typedef struct tagMyStruct
{ 
    int iNum;
    long lLength;
}MyStruct;
上面的tagMyStruct是标识符，而MyStruct是变量类型（相当于int,char等）。
——————————————————————————————————————————————————————————————————————————
typedef struct tagMyStruct
{ 
int iNum;
long lLength;
}MyStruct;
在C中，这个申明后申请结构变量的方法有两种：
（1）struct tagMyStruct 变量名
（2）MyStruct 变量名
在c++中可以有
（1）struct tagMyStruct 变量名
（2）MyStruct 变量名
（3）tagMyStruct 变量名
——————————————————————————————————————————————————————————————————————————

3.在main中无论是定义结构体tmp还是结构体指针p都是正确的

4.具体题目中细节问题。Line 131中要加2是因为参照日期2017.9.5是周二；Line 132
在最后计算星期是对7取余，因此在数组weekname中Sunday应该对应的下标是0而不是7
**************************************************************************/

//c使用typedef的方法，其中main函数里用date定义指针或结构体，以及malloc里面
//的date均可以使用struct Date来替代，但是如果typedef struct声明中没有用Date，
//那就只能在main函数中用date
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define ISLEAP(x) (x%4==0&&x%100!=0 || x%400==0)?1:0

int buf[3001][13][32];

char monthname[13][10] = {
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

char weekname[7][10]={
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

int dayofmonth[13][2]={
    0,0,
    31,31,
    28,29,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31
};

typedef struct Date{
    int day;
    int month;
    int year;
}date;

void nextday(date* tmp){
    tmp->day++;
    if(tmp->day > dayofmonth[tmp->month][ISLEAP(tmp->year)]){
        tmp->day = 1;
        tmp->month++;
        if(tmp->month > 12){
            tmp->month = 1;
            tmp->year++;
        }
    }
}


int main(){
    int d, y;
    char m[10];
    int i, days;
    int cnt = 0;
    
    date *p = (date*)malloc(sizeof(date));
    p->year = 0;
    p->month = 1;
    p->day = 1;
    while(p->year <= 3001){
        buf[p->year][p->month][p->day] = cnt++;
        nextday(p);
    }
    
    /*
    date tmp;
    tmp.year = 0;
    tmp.month = 1;
    tmp.day = 1;
    while(tmp.year <=3001){
        buf[tmp.year][tmp.month][tmp.day] = cnt;
        nextday(&tmp);
        cnt++;
    }
    */
    while(scanf("%d %s %d", &d, m, &y) != EOF){
        for(i=1; i<13; i++)
            if(strcmp(m, monthname[i]) == 0)
                break;
 
        days = buf[y][i][d] - buf[2017][9][5];
        days += 2;
        printf("%s\n", weekname[(days%7+7)%7]);
    }
    return 0;
}

//使用c++编写的，主要区别就在于nextday函数作为成员函数的使用，以及
//在结构体的定义中一些小的区别
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define ISLEAP(x) (x%4==0&&x%100!=0 || x%400==0)?1:0

int buf[3001][13][32];

char monthname[13][10] = {
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

char weekname[7][10]={
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

int dayofmonth[13][2]={
    0,0,
    31,31,
    28,29,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31
};

struct Date{
    int day;
    int month;
    int year;
    void nextday(){
        day++;
        if(day > dayofmonth[month][ISLEAP(year)]){
            day = 1;
            month++;
            if(month > 12){
                month = 1;
                year++;
            }
        }
    }
};

int main(){
    int d, y;
    char m[10];
    int i, days;
    int cnt = 0;

    struct Date *p = (struct Date*)malloc(sizeof(struct Date));
    p->year = 0;
    p->month = 1;
    p->day = 1;
    while(p->year <= 3001){
        buf[p->year][p->month][p->day] = cnt++;
        p->nextday();
    }
    
    while(scanf("%d %s %d", &d, m, &y) != EOF){
        for(i=1; i<13; i++)
            if(strcmp(m, monthname[i]) == 0)
                break;
 
        days = buf[y][i][d] - buf[2017][9][5];
        days += 2;
        printf("%s\n", weekname[(days%7+7)%7]);
    }
    return 0;
}



#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define ISLEAP(x) (x%4==0&&x%100!=0 || x%400==0)?1:0

int buf[3001][13][32];

char monthname[13][10] = {
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

char weekname[7][10]={
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

int dayofmonth[13][2]={
    0,0,
    31,31,
    28,29,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31,
    31,31,
    30,30,
    31,31,
    30,30,
    31,31
};

typedef struct Date{
    int day;
    int month;
    int year;
    void nextday(){
        day++;
        if(day > dayofmonth[month][ISLEAP(year)]){
            day = 1;
            month++;
            if(month > 12){
                month = 1;
                year++;
            }
        }
    }
}date;

int main(){
    int d, y;
    char m[10];
    int i, days;
    int cnt = 0;
    
    //Date tmp;
    date tmp;
    tmp.year = 0;
    tmp.month = 1;
    tmp.day = 1;
    while(tmp.year <=3001){
        buf[tmp.year][tmp.month][tmp.day] = cnt;
        tmp.nextday();
        cnt++;
    }

    while(scanf("%d %s %d", &d, m, &y) != EOF){
        for(i=1; i<13; i++)
            if(strcmp(m, monthname[i]) == 0)
                break;
 
        days = buf[y][i][d] - buf[2017][9][5];
        days += 2;
        printf("%s\n", weekname[(days%7+7)%7]);
    }
    return 0;
}