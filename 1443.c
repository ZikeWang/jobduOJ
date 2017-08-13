/*********************************1443************************************
题目描述：
A为一个方阵，则Tr A表示A的迹（就是主对角线上各项的和），现要求Tr(A^k)%9973。
输入：
数据的第一行是一个T，表示有T组数据。
每组数据的第一行有n(2 <= n <= 10)和k(2 <= k < 10^9)两个数据。接下来有n行，
每行有n个数据，每个数据的范围是[0,9]，表示方阵A的内容。
输出：
对应每组数据，输出Tr(A^k)%9973。
样例输入：
2
2 2
1 0
0 1
3 99999999
1 2 3
4 5 6
7 8 9
样例输出：
2
2686
**************************************************************************/

#include <stdio.h>

#define module 9973

int matrix[11][11];
int newmatrix[11][11];
int temp[11][11];

int main(void){
	int T, n, k;
	int i, j, h, cnt, x, y, tmp, result, sum;
	while(scanf("%d", &T) != EOF){
		for(cnt=0; cnt<T; cnt++){
			scanf("%d %d", &n, &k);
			for(i=1; i<=n; i++)
				for(j=1; j<=n; j++){
					scanf("%d", &matrix[i][j]);
				}
			for(i=1; i<=n; i++)
				for(j=1; j<=n; j++){
					if(i == j)
						newmatrix[i][j] = 1;
					else
						newmatrix[i][j] = 0;
				}
			while(k != 0){
				if(k%2 == 1){
					for(i=1; i<=n; i++)
						for(j=1; j<=n; j++)
							temp[i][j] = newmatrix[i][j];
					for(i=1; i<=n; i++)
						for(j=1; j<=n; j++){
							sum = 0;
							tmp = 0;
							for(h=1; h<=n; h++){
								tmp = temp[i][h] * matrix[h][j];
								tmp %= module;
								sum = sum + tmp;
								sum %= module;
							}
							newmatrix[i][j] = sum;
						}
				}
				k /= 2;
				for(i=1; i<=n; i++)
					for(j=1; j<=n; j++)
						temp[i][j] = matrix[i][j];
				for(i=1; i<=n; i++)
					for(j=1; j<=n; j++){
						sum = 0;
						tmp = 0;
						for(h=1; h<=n; h++){
							tmp = temp[i][h] * temp[h][j];
							tmp %= module;
							sum = sum + tmp;
							sum %= module;
						}
						matrix[i][j] = sum;
					}
			}
			result = 0;
			for(i=1; i<=n; i++){
				result += newmatrix[i][i];
				result %= module;
			}
			printf("%d\n", result);
		}
	}
	return 0;
}

/*************************************************************
有两点需要注意：
避免在变量定义时使用关键字如new
涉及到次数较大的幂级数运算时，优先考虑二分求幂法
**************************************************************/