/*********************************1196************************************
题目描述：
用一维数组存储学号和成绩，然后，按成绩排序输出。
输入：
输入第一行包括一个整数N(1<=N<=100)，代表学生的个数。
接下来的N行每行包括两个整数p和q，分别代表每个学生的学号和成绩。
输出：
按照学生的成绩从小到大进行排序，并将排序后的学生信息打印出来。
如果学生的成绩相同，则按照学号的大小进行从小到大排序。
样例输入：
3
1 90
2 87
3 92
样例输出：
2 87
1 90
3 92
**************************************************************************/

#include <stdio.h>

int id[101];
int mark[101];

int main(){
	int n;
	int i, j, tmp_id, tmp_mark;
	while(scanf("%d", &n) != EOF){
		for(i=0; i<n; i++){
			scanf("%d %d", &id[i], &mark[i]);
		}
		for(i=0; i<n; i++)
			for(j=0; j<n-1-i; j++)
				if(mark[j] > mark[j+1]){
					tmp_mark = mark[j];
					mark[j] = mark[j+1];
					mark[j+1] = tmp_mark;

					tmp_id = id[j];
					id[j] = id[j+1];
					id[j+1] = tmp_id;
				}
				else if(mark[j] == mark[j+1]){
					if(id[j] > id[j+1]){
						tmp_mark = mark[j];
						mark[j] = mark[j+1];
						mark[j+1] = tmp_mark;

						tmp_id = id[j];
						id[j] = id[j+1];
						id[j+1] = tmp_id;
					}
				}
		for(i=0; i<n; i++)
			printf("%d %d\n", id[i], mark[i]);
	}
	return 0;
}

//（一维数组表示是否是只能用一个一维数组？）参看了其他代码，多为使用了一个结构体数组
//和一个一维数组，所以本解法这种使用两个一维数组的方案应该没问题
//要看清题目要求：若成绩相同还要用学号排序。Line 44~53为后来添加