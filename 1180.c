/*********************************1180************************************
题目描述：
输入一个N维矩阵，判断是否对称。
输入：
输入第一行包括一个数：N(1<=N<=100)，表示矩阵的维数。
接下来的N行，每行包括N个数，表示N*N矩阵的元素。
输出：
可能有多组测试数据，对于每组数据，
输出"Yes!”表示矩阵为对称矩阵。
输出"No!”表示矩阵不是对称矩阵。
样例输入：
4
16 19 16 6 
19 16 14 5 
16 14 16 3 
6 5 3 16 
2
1 2
3 4
样例输出：
Yes!
No!
**************************************************************************/

#include <stdio.h>

int matrix[101][101];

int main(){
	int n;
	int i, j, flag;
	while(scanf("%d", &n) != EOF){
		flag = 1;

		for(i=1; i<=n; i++)
			for(j=1; j<=n; j++){
				matrix[i][j] = '\0';
			}

		for(i=1; i<=n; i++)
			for(j=1; j<=n; j++){
				scanf("%d", &matrix[i][j]);
			}

		for(i=1; i<=n; i++){
			for(j=i+1; j<=n; j++){
				if(matrix[i][j] != matrix[j][i])
					flag = 0;
				if(!flag)
					break;
			}
			if(!flag)
				break;
		}

		if(flag)
			printf("Yes!\n");
		else
			printf("No!\n");
	}
	return 0;
}

