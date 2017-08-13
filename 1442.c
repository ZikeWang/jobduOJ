/*********************************1442************************************
题目描述：
Xinlv wrote some sequences on the paper a long time ago, they might be 
arithmetic or geometric sequences. The numbers are not very clear now, 
and only the first three numbers of each sequence are recognizable. Xinlv 
wants to know some numbers in these sequences, and he needs your help.
输入：
The first line contains an integer N, indicting that there are N sequences. 
Each of the following N lines contain four integers. The first three 
indicating the first three numbers of the sequence, and the last one is K, 
indicating that we want to know the K-th numbers of the sequence.
You can assume 0 < K <= 10^9, and the other three numbers are in the 
range [0, 2^63). All the numbers of the sequences are integers. And the 
sequences are non-decreasing.
输出：
Output one line for each test case, that is, the K-th number module (%) 200907.
样例输入：
2
1 2 3 5
1 2 4 5
样例输出：
5
16
**************************************************************************/

#include <stdio.h>

#define module 200907

long long num[3];

long long power(long long range, int k){
	long long result = 1;
	range %= module;
	while(k != 0){
		if(k%2 == 1)
			result *= range;
		result %=module;
		k /= 2;
		range *= range;
		range %= module;
	}
	return result;
}

int main(void){
	int N, k;
	int i, j;
	long long range, result;
	while(scanf("%d", &N) != EOF){
		for(i=0; i<N; i++){
			for(j=0; j<3; j++)
				scanf("%lld", num+j);
			scanf("%d", &k);
			if(num[2]-num[1] == num[1]-num[0]){
				range = num[2] - num[1];
				result = ( (num[0]%module) + (((k-1)%module)*(range%module))%module )%module;
			}
			else if(num[1]*num[1] == num[0]*num[2]){
				range = num[1] / num[0];
				result = ((num[0]%module) * (power(range, k-1))%module)%module;
			}
			printf("%lld\n", result);
		}
	}
	return 0;
}

/************************************************************
首先应该估算数据的范围，临界情况：
很显然，对于等差数列，考虑极端情况0，2^62-1，2^63-2；k=10^9，
那么第k个数为(2^62-1)*(10^9-1)远远超过了long long(2^64可表示
的范围)；对于等比数列而言，考虑极端情况1，sqrt(2^63-1)，2^63-1，
sqrt(2^63-1)大于2^31，pow(2^31, 10^9-1)则更大，因此必须考虑
大数问题

对于这种大数运算特别是结果要求模的，为了防止溢出等问题要注意
运用求模运算的分解，具体来说就是对加法和乘法运算的求模分解。

另外如果涉及到大的幂运算，要考虑运用二分求幂的方法
*************************************************************/