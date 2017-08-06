/**********1070************************************************************
题目描述：
输入年、月、日，计算该天是本年的第几天。
输入：
包括三个整数年(1<=Y<=3000)、月(1<=M<=12)、日(1<=D<=31)。
输出：
输入可能有多组测试数据，对于每一组测试数据，
输出一个整数，代表Input中的年、月、日对应本年的第几天。
样例输入：
1990 9 20
2000 5 1
样例输出：
263
122
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

int buf[3001][12][31];

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
	int this_year, this_month, this_day;
	while(scanf("%d %d %d", &this_year, &this_month, &this_day) != EOF){
		printf("%d\n", buf[this_year][this_month][this_day] - buf[this_year][1][1] + 1);
	}
	return 0;
}

/*************************************************************************
有两点需要注意：
1.dayofMonth数组第一组数据为0,0是为了将数据后移使得数组下标与年份数字对应
2.在结构体内定义的nextday()函数应注意在修改month和day的逻辑顺序，由于计算
新day的值要使用原month，因此更新month值应该在更新day值之后进行。若采取直接
将day值置1的处理办法，则无需考虑逻辑先后顺序
**************************************************************************/