/*********************************1179************************************
题目描述：
输入n，
求y1=1!+3!+...m!(m是小于等于n的最大奇数）
y2=2!+4!+...p!(p是小于等于n的最大偶数)。
输入：
每组输入包括1个整数：n
输出：
可能有多组测试数据，对于每组数据，
输出题目要求的y1和y2
样例输入：
4
样例输出：
7 26
**************************************************************************/

#include <stdio.h>

long long mul(long long m){
	if(m == 1)
		return 1;
	else
		return m*mul(m-1);
}

int main(){
	long long n;
	long long p, m, y1, y2;
	while(scanf("%lld", &n) != EOF){
		if(n % 2 == 0){
			m = n - 1;
			p = n;
		}
		else{
			m = n;
			p = n - 1;
		}

		y1 = 0;
		y2 = 0;
		
		while(m >= 1){
			y1 += mul(m);
			m -= 2;
		}

		while(p >= 2){
			y2 += mul(p);
			p -= 2;
		}

		printf("%lld %lld\n", y1, y2);
	}
	return 0;
}

/*******************************************************
NOTICE!!!
之前一直提交不通过的问题在于数据的类型定义的过小，使用了
int类型，当数据改为long long类型进行定义以后，就可以了。

对于题目中涉及数据的，数据没有给出明确范围的，一定要考虑
数据的大小和范围问题，要考虑是否采用较大的数据类型例如
long和long long，甚至要考虑到是否涉及到高精度数从而可能
字符数组、结构体等相关操作。
********************************************************/