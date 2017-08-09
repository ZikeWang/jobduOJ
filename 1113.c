/**********1113***********************************************************
题目描述：
由正整数1，2，3……组成了一颗特殊二叉树。我们已知这个二叉树的最后一个结点是n。
现在的问题是，结点m所在的子树中一共包括多少个结点。
比如，n = 12，m = 3那么上图中的结点13，14，15以及后面的结点都是不存在的，
结点m所在子树中包括的结点有3，6，7，12，因此结点m的所在子树中共有4个结点。
输入：
    输入数据包括多行，每行给出一组测试数据，包括两个整数m，n 
    (1 <= m <= n <= 1000000000)。最后一组测试数据中包括两个0，
    表示输入的结束，这组数据不用处理。
输出：
    对于每一组测试数据，输出一行，该行包含一个整数，给出结点m所在子树中
    包括的结点的数目。
样例输入：
3 12
0 0
样例输出：
4
**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

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
	int m, n, mno, nno, mlast, mfirst, subsum, result;
	while(scanf("%d %d", &m, &n) != EOF){
		if(m==0 && n==0)
			break;
		mno = search(m);
		nno = search(n);
		mfirst = m * pow(2, nno-mno);
		mlast = (m+1) * pow(2, nno-mno) - 1;
		if(mlast>=n && n>=mfirst) 
			result = sum(mno, nno) - (mlast-n);
		else if(n > mlast)
			result = sum(mno, nno);
		else
			result = sum(mno, nno-1);
		printf("%d\n", result);
	}
	return 0;
}
