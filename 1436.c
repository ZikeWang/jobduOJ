/**********1436*************************************************************
题目描述：
Long time ago , Kitty lived in a small village. The air was fresh and the scenery was very beautiful. 
The only thing that troubled her is the typhoon.
When the typhoon came, everything is terrible. It kept blowing and raining for a long time. 
And what made the situation worse was that all of Kitty's walls were made of wood.
One day, Kitty found that there was a crack in the wall. The shape of the crack is 
a rectangle with the size of 1×L (in inch). Luckly Kitty got N blocks and a saw(锯子) from her neighbors.
The shape of the blocks were rectangle too, and the width of all blocks were 1 inch. 
So, with the help of saw, Kitty could cut down some of the blocks
(of course she could use it directly without cutting) and put them in the crack, 
and the wall may be repaired perfectly, without any gap.
Now, Kitty knew the size of each blocks, and wanted to use as fewer as possible of 
the blocks to repair the wall, could you help her ?
输入：
The problem contains many test cases, please process to the end of file( EOF ).
Each test case contains two lines.
In the first line, there are two integers L(0<L<1000000000) and N(0<=N<600) which
mentioned above.
In the second line, there are N positive integers. The ith integer Ai(0<Ai<1000000000 ) 
means that the ith block has the size of 1×Ai (in inch).
输出：
For each test case , print an integer which represents the minimal number of blocks are needed.
If Kitty could not repair the wall, just print "impossible" instead.
样例输入：
5 3
3 2 1
5 2
2 1
样例输出：
2
impossible
**************************************************************************/

#include <stdio.h>

void quicksort(int *a, int left, int right){
	if(left > right)
		return;
	int i = left;
	int j = right;
	int temp = *(a+left);
	while(i != j){
		while(a[j]<=temp && i<j)
			j--;
		while(a[i]>=temp && i<j)
			i++;
		if(i<j){
			int tmp = *(a+i);
			*(a+i) = *(a+j);
			*(a+j) = tmp;
		}
	}
	*(a+left) = *(a+i);
	*(a+i) = temp;
	quicksort(a,left,i-1);
	quicksort(a,i+1,right);
}

int main(void){
	int L, N, A[600], len, result;
	int i;
	while(scanf("%d %d", &L, &N) != EOF){
		for(i=0; i<N; i++)
			scanf("%d", A+i);
		quicksort(A, 0, N-1);
		if(L <= A[0]){
			result = 1;
			printf("%d\n", result);
		}
		else{
			len = A[0];
			result = 1;
			i = 1;
			while(len < L && i < N){
				if( (len+A[i]) <= L ){
					len += A[i++];
					result++;
				}
				else{
					len += A[i++];
					result++;
					break;
				}
			}
			if(i <= N && len >= L)
				printf("%d\n", result);
			else if(i = N && len < L)
				printf("impossible\n");
		}
	}
	return 0;
}

/*************************************************
判断条件过于复杂，之前一直WE在于判断条件中指明了
要求len>=L，但是在贪心计算过程中，while的判断部分
并没有更新len的值，只是作为右值计算判断，而后面的
else部分一开始就直接跳出了循环，并没有更新len的值，
从而导致判断时出现错误。
在贪心算法中可以简化这种判断过程，如使用flag的方法
**************************************************/