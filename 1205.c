/*********************************1205************************************
题目描述：
N阶楼梯上楼问题：一次可以走两阶或一阶，问有多少种上楼方式。（要求采用非递归）
输入：
输入包括一个整数N,(1<=N<90)。
输出：
可能有多组测试数据，对于每组数据，
输出当楼梯阶数是N时的上楼方式个数。
样例输入：
4
样例输出：
5
**************************************************************************/
//数组+动态规划的方式，动态规划状态转移方程为array[i] = array[i-1] + array[i-2];
/*
#include <stdio.h>

int main(){
	int n;
	int i;
	long long array[100];
	while(scanf("%d", &n) != EOF){
		array[1] = 1;
		array[2] = 2;
		array[3] = 3;
		for(i=4; i<100; i++)
			array[i] = array[i-1] + array[i-2];
		printf("%lld\n", array[n]);
	}
	return 0;
}
*/

//line 20一开始定义为int偏小，导致n过大时溢出变成负数，当题目没有明确告诉
//一些值或者变量的范围时，首先要估算值的大小，选择使用合理的数据类型和方法

//非数组方式：
#include <stdio.h>

int main(){
	int n;
	int i;
	long long f1, f2, f3;
	while(scanf("%d", &n) != EOF){
		i = 3;
		f1 = 1;
		f2 = 2;
		f3 = 3;
		while(i < n){
			f1 = f2;
			f2 = f3;
			f3 = f1 + f2;
			i++;
		}
		if(n == 1)
			printf("1\n");
		else if(n == 2)
			printf("2\n");
		else
			printf("%lld\n", f3);
		}
	return 0;
}