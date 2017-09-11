/*********************************1191************************************
题目描述：
编写一个程序输入一个mXn的矩阵存储并输出，并且求出每行的最大值和每行的总和。
要求把每行总和放入每行最大值的位置，如果有多个最大值，取下标值最小的那一个
作为最大值。最后将结果矩阵输出。
输入：
输入的第一行包括两个整数m和n(1<=m,n<=100)，分别代表矩阵的行和列的维数。
接下来的m行每行有n个数，代表矩阵的元素。
输出：
可能有多组测试数据，对于每组数据，输出按题目要求执行后的矩阵。
样例输入：
3 3
1 1 1
1 1 1
1 1 1
3 3
3 2 3
2 3 2
3 2 3
样例输出：
3 1 1
3 1 1
3 1 1
8 2 3
2 7 2
8 2 3
**************************************************************************/

#include <stdio.h>

int matrix[101][101];
//int maxno[101];

int main(){
	int m, n;
	int i, j, flag, max, sum;
	//int cnt;
	while(scanf("%d %d", &m, &n) != EOF){
		for(i=1; i<=m; i++)
			for(j=1; j<=n; j++)
				scanf("%d", &matrix[i][j]);
		for(i=1; i<=m; i++){
			max = 0;
			sum = 0;
			//cnt = 0;
			flag = 0;
			for(j=1; j<=n; j++){
				sum += matrix[i][j];
				if(matrix[i][j] > max){
					//cnt = 1;
					//maxno[0] = matrix[i][j];
					flag = j;
					max = matrix[i][j];
				}
				//else if(matrix[i][j] == max){
					//maxno[cnt++] = matrix[i][j];
				//}
			}
			matrix[i][flag] = sum;
		}
		for(i=1; i<=m; i++){
			for(j=1; j<n; j++)
				printf("%d ", matrix[i][j]);
			printf("%d\n", matrix[i][n]);
		}
	}
	return 0;
}

//这道题的解体思路一开始过于复杂。注释部分代码的作用是将所有最大值都进行记录
//并输出，但是仔细阅读题目意思可以明确只要求输出下标最小的，显然在对矩阵的每
//一行进行遍历时，第一个找到的最大值即为下标最小的，后面再找到的不用处理可以
//直接跳过，因此只要通过比较发现了新的最大值，保存下标即可

/*编写一个程序输入一个5X6的矩阵存储并输出，
并且求出每行的最大值和每行的总和要求把每行总和放入每行最大值的位置， 
最后把结果矩阵，每行最大值及其原下标及其总和输出*/

#include <stdio.h>

int main(){
    int matrix[5][6];
    int max[5];
    int index[5][6];
    int cnt[5];
    int sum[5];
    int i, j;
    for(i=0; i<5; i++){
        for(j=0; j<6; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    for(i=0; i<5; i++){
        cnt[i] = 1;
        max[i] = matrix[i][0];
        index[i][cnt[i]-1] = 0;
        sum[i] = max[i];
        for(j=1; j<6; j++){
            sum[i] += matrix[i][j];
            if(matrix[i][j] > max[i]){
                max[i] = matrix[i][j];
                index[i][cnt[i]-1] = j;
            }
            else if(matrix[i][j] == max[i]){
                cnt[i]++;
                index[i][cnt[i]-1] = j;
            }
        }
        for(j=0; j<cnt[i]; j++){
            matrix[i][index[i][j]] = sum[i];
        }
    }
    for(i=0; i<5; i++){
        for(j=0; j<6; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i=0; i<5; i++){
        printf("Line %d : \n", i);
        for(j=0; j<cnt[i]; j++){
            printf("max=%d, index=%d\n", max[i], index[i][j]);
        }
        printf("sum=%d\n\n", sum[i]);
    }
}
