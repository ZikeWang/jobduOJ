/**********1194***********************************************************
题目描述：
输入一个整数，将其转换成八进制数输出。
输入：
输入包括一个整数N(0<=N<=100000)。
输出：
可能有多组测试数据，对于每组数据，
输出N的八进制表示数。
样例输入：
7
8
9
样例输出：
7
10
11
**************************************************************************/

#include <stdio.h>
#include <string.h>

int main(void){
	int N;
	int ans[30], cnt, i;
	while(scanf("%d", &N) != EOF){
		cnt = 0;
		do{
			ans[cnt++] = N % 8;
			N /= 8;
		}while(N);
		for(i=cnt-1; i>=0; i--)
			printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}