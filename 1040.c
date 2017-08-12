/**********1040***********************************************************
题目描述：
Output the k-th prime number.
输入：
k≤10000
输出：
The k-th prime number.
样例输入：
3
7
样例输出：
5
17
**************************************************************************/
#include <stdio.h>
#include <math.h>

/*int prime[10001];
int hash[30000];
int cnt;

void init(){
	int i, j;
	cnt = 0;
	for(i=0; i<=30000; i++)
		hash[i] = 0;
	for(i=2; i<=30000; i++){
		if(hash[i] == 1)
			continue;
		else{
			prime[cnt++] = i;
			for(j=i*i; j<=30000; j+=i)
				hash[j] = 1;
		}
	}
}*/

int isPrime(int x){
	int i, bound;
	if(x == 1)
		return 0;
	else{
		bound = (int)sqrt(x) + 1;
		for(i=2; i<bound; i++){
			if(x%i == 0)
				return 0;
		}
		return 1;
	}
}

int main(void){
	int k;
	int cnt, x, flag;
	while(scanf("%d", &k) != EOF){
		cnt = 0;
		flag = 0;
		x = 2;
		while(cnt < k){
			flag = isPrime(x);
			if(flag == 1)
				cnt++;
			x++;
		}
		printf("%d\n", x-1);
	}
	return 0;
}

/**************************************************************
素数筛法数组定义过大出现运行时错误，可以定义的最大数目可能和机
器性能有关
该程序提交后没有超时可能是因为测试用例并没有涉及到临界极端情况
***************************************************************/