/*********************************1122************************************
题目描述：
名名的妈妈从外地出差回来，带了一盒好吃又精美的巧克力给名名（盒内共有 N 块
巧克力，20 > N >0）。
妈妈告诉名名每天可以吃一块或者两块巧克力。
假设名名每天都吃巧克力，问名名共有多少种不同的吃完巧克力的方案。
例如：
如果N=1，则名名第1天就吃掉它，共有1种方案；
如果N=2，则名名可以第1天吃1块，第2天吃1块，也可以第1天吃2块，共有2种方案；
如果N=3，则名名第1天可以吃1块，剩2块，也可以第1天吃2块剩1块，所以名名共有
2+1=3种方案；
如果N=4，则名名可以第1天吃1块，剩3块，也可以第1天吃2块，剩2块，共有3+2=5种
方案。
现在给定N，请你写程序求出名名吃巧克力的方案数目。
输入：
输入只有1行，即整数N。
输出：
可能有多组测试数据，对于每组数据，
输出只有1行，即名名吃巧克力的方案数。
样例输入：
4
样例输出：
5
**************************************************************************/

#include <stdio.h>

int main(){
	int n;
	int F[20], i;
	F[1] = 1;
	F[2] = 2;
	while(scanf("%d", &n) != EOF){
		for(i=3; i<=n; i++)
			F[i] = F[i-1] + F[i-2];
		printf("%d\n", F[n]);
	}

	return 0;
}