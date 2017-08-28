/*********************************1200************************************
题目描述：
    输入一个四行五列的矩阵，找出每列最大的两个数。
输入：
    输入第一行包括一个整数n(1<=n<=1000)，接下来的四行每行包括五个整数。
    代表一个四行五列的矩阵，矩阵元素全部是整数。
输出：
    可能有多组测试数据，对于每组数据，按照样例输出的格式将每列最大的两个数
    输出，如果最大的两个数中的一个数在这一列中有多个相同的值，则行值取行值
    小的那一个。输出时要保留原矩阵的行列顺序，即在原矩阵中行值小的，在输出
    矩阵中的行值依然小。
样例输入：
1
1  2   4  9  8
-1  4  9  8  8
12  9  8  7  0
7   8  9  7  0
样例输出：
12 9 9 9 8 
7 8 9 8 8 
提示：
每个数字后面都要输出一个空格
**************************************************************************/

#include <stdio.h>

int matrix[5][6];
int out[2][5];

struct Column{
	int value;
	int raw;
}column[4];

void swap(int i, int j){
	int tmp_value = column[i].value;
	column[i].value = column[j].value;
	column[j].value = tmp_value;

	int tmp_raw = column[i].raw;
	column[i].raw = column[j].raw;
	column[j].raw = tmp_raw;
}

int main(){
	int n;
	int i, j, k, l;
	scanf("%d", &n);
	while(n-- > 0){
		for(i=1; i<=4; i++)
			for(j=1; j<=5; j++)
				scanf("%d", &matrix[i][j]);

		for(j=1; j<=5; j++){
			for(i=1; i<=4; i++){
				column[i-1].value = matrix[i][j];
				column[i-1].raw = i;
			}

			for(k=0; k<4; k++)
				for(l=0; l<3-k; l++)
					if(column[l].value < column[l+1].value)
						swap(l, l+1);

			if(column[0].raw > column[1].raw){
				out[0][j-1] = column[1].value;
				out[1][j-1] = column[0].value;
			}
			else{
				out[0][j-1] = column[0].value;
				out[1][j-1] = column[1].value;
			}
		}

		for(i=0; i<2; i++){
			for(j=0; j<5; j++)
				printf("%d ", out[i][j]);
			printf("\n");
		}
	}
	return 0;
}