/**********1176***********************************************************
题目描述：
有一棵树，输出某一深度的所有节点，有则输出这些节点，无则输出EMPTY。该树是完全二叉树。
输入：
输入有多组数据。
每组输入一个n(1<=n<=1000)，然后将树中的这n个节点依次输入，再输入一个d代表深度。
输出：
输出该树中第d层得所有节点，节点间用空格隔开，最后一个节点后没有空格。
样例输入：
4
1 2 3 4
2
样例输出：
2 3
**************************************************************************/

#include <stdio.h>
#include <math.h>

int node[1001];

int sum(int i, int j){
	int k;
	int result = 0;
	for(k=0; k<=j-i; k++){
		result += pow(2, k);
	}
	return result;
}

int search(int target){
	int j = 1;
	int total = sum(1,j);
	while(total < target)
		total = sum(1, ++j);
	return j;
}

int main(void){
	int n, d;
	int maxline, dtotal1, dtotal2;
	int i;
	while(scanf("%d", &n) != EOF){
		for(i=0; i<n; i++)
			scanf("%d", node+i);
		scanf("%d", &d);
		maxline = search(n);
		if(d < maxline){
			dtotal1 = sum(1, d-1);
			dtotal2 = sum(1, d);
			for(i=dtotal1; i<dtotal2-1; i++)
				printf("%d ", node[i]);
			printf("%d\n", node[dtotal2-1]);
		}
		else if(d == maxline){
			dtotal1 = sum(1, d-1);
			for(i=dtotal1; i<n-1; i++)
				printf("%d ", node[i]);
			printf("%d\n", node[n-1]);
		}
		else
			printf("EMPTY\n");
	}
	return 0;
}

/*******************************************
该sum()和search()函数适用于类似的完全二叉树
********************************************/