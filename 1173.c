/********1173*****************************************************
题目描述：
输入数组长度 n 
输入数组 a[1...n] 
输入查找个数m 
输入查找数字b[1...m] 
输出 YES or NO  查找有则YES 否则NO 。

输入：
输入有多组数据。
每组输入n，然后输入n个整数，再输入m，然后再输入m个整数（1<=m<=n<=100）。

输出：
如果在n个数组中输出YES否则输出NO。

样例输入：
5
1 5 2 4 3
3
2 5 6
样例输出：
YES
YES
NO
******************************************************************/

/*
//线性查找法
#include <stdio.h>

int main(void){
	int n, m;
	while( scanf("%d", &n) != EOF ){
		int a[100] = {0};
		int b[100] = {0};
		int i, j, flag;
		for(i=0; i<n; i++)
			scanf("%d", a+i);
		scanf("%d", &m);
		for(i=0; i<m; i++)
			scanf("%d", b+i);
		for(i=0; i<m; i++){
			flag = 0;
			for(j=0; j<n; j++)
				if( b[i] == a[j] ){
					flag = 1;
					break;
				}
			if( flag )
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
	return 0;
}
*/

//二分查找法
#include <stdio.h>

void quicksort(int *a, int left, int right){
	if(left > right)
		return;
	int i = left;
	int j = right;
	int temp = *(a+left);
	while(i != j){
		while(a[j]>=temp && i<j)
			j--;
		while(a[i]<=temp && i<j)
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
	int n, m;
	while( scanf("%d", &n) != EOF ){
		int a[100] = {0};
		int b[100] = {0};
		int i, flag, top, base, mid;
		for(i=0; i<n; i++)
			scanf("%d", a+i);
		scanf("%d", &m);
		for(i=0; i<m; i++)
			scanf("%d", b+i);
		quicksort(a,0,n-1);
		for(i=0; i<m; i++){
			flag = 0;
			base = 0;
			top = n-1;
			while(base <= top){
				mid = (top+base)/2;
				if( b[i] == a[mid] ){
					flag = 1;
					break;
				}
				else if( b[i] > a[mid] ){
					base = mid+1;
					continue;
				}
				else if( b[i] < a[mid] ){
					top = mid-1;
					continue;
				}
			}
			if( flag )
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
	return 0;
}

/*************************************************************************
1.使用二分查找时，在更新top或者base值时注意往前或往后移动一位，即使用mid-1
或者mid+1，而不是直接将mid值赋给top或base
2.使用二分查找前要排好序，否则二分将没有意义
3.使用快排时注意不能丢掉了返回条件，即在left>right时要return，否则调用函数
没有出口无法跳出递归
**************************************************************************/

/**************************使用二分查找的方法进行定界*************************
//A为降序数组
int binary_search(int *A, int base, int top, int target){
	if(base>top)
		return -1;
	int mid;
	while(base <= top){
		mid = (base+top)/2;
		if(target == A[mid])
			return mid;
		else if(target > A[mid])
			top = mid - 1;
		else if(target < A[mid])
			base = mid + 1;
	}
	return top;	//返回>=target的最小下标点；若要得到<=target的最小下标点，则return base
	//需要注意的是如果target比数组最大值A[base]还大，则return top时返回-1越界了
	//或者target比数组最小值A[top]还小,同理如果return base则返回top+1同样越界了
}
********************************************************************************/