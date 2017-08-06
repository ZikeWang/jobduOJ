/********1186******************************************************
题目描述：
给出年分m和一年中的第n天，算出第n天是几月几号。
输入：
输入包括两个整数y(1<=y<=3000)，n(1<=n<=366)。
输出：
可能有多组测试数据，对于每组数据，
按 yyyy-mm-dd的格式将输入中对应的日期打印出来。
样例输入：
2000 3
2000 31
2000 40
2000 60
2000 61
2001 60
样例输出：
2000-01-03
2000-01-31
2000-02-09
2000-02-29
2000-03-01
2001-03-01
**************************************************************************/

#include <stdio.h>
#include <string.h>
using namespace std;

#define ISLEAP(x) (x%4==0)&&(x%100!=0) || x%400==0 ?1:0

int dayofMonth[13][2] = {
	0 , 0 ,
	31, 31,
	28, 29,
	31, 31,
	30, 30,
	31, 31,
	30, 30,
	31, 31,
	31, 31,
	30, 30,
	31, 31,
	30, 30,
	31, 31
};

int buf[3001][13][32];

struct Date{
	int year;
	int month;
	int day;
	void nextday(){
		day++;
		if( day > dayofMonth[month][ISLEAP(year)] ){
			day -= dayofMonth[month][ISLEAP(year)];
			month++;
		}
		if( month > 12){
			year++;
			month -= 12;
		}
	}
};

int main(void){
	Date tmp;
	tmp.year = 0;
	tmp.month = 1;
	tmp.day = 1;
	int cnt = 0;
	while(tmp.year < 3001){
		buf[tmp.year][tmp.month][tmp.day] = cnt;
		tmp.nextday();
		cnt++;
	}
	int this_year, N;
	while(scanf("%d %d", &this_year, &N) != EOF){
		int flag = 0;
		int COUNT = buf[this_year][1][1] + N - 1;
		int j, k;
		for(j=1; j<13; j++){
			for(k=1; k<32; k++){
				if(buf[this_year][j][k] == COUNT)
					flag = 1;
				if(flag)
					break;
			}
			if(flag)
				break;
		}
		printf("%04d-%02d-%02d\n", this_year, j, k);
	}
	return 0;
}

/*************************************************************************
有四个问题需要注意：
1.在定义buf数组时，之前是按照buf[3001][12][31]来定义的，这样的话导致按照
月份数字或日数字作为下标直接访问时可能导致越界，例如在计算cnt时直接使用
buf[tmp.year][tmp.month][tmp.day]，当tmp_month=12或者tmp_day=31时没有对应
的buf[][12][]或者buf[][][31]，因此需要增加将buf的第二维和第三维各增加一个
大小
2.在循环遍历时若从头开始曾开销太大（n^3），注意到计算的是输入年份当年中的
第n天，因此只需调整年份为当年即可
3.break语句每次只能跳出当前所在的一层循环，即所在的最内层循环，若要一次跳
出多层循环，不建议使用goto语句，可以设置一个flag来标志是否要跳出所有循环
4.输出格式控制问题。例如本题中%4d控制长度为4，前补零
**************************************************************************/