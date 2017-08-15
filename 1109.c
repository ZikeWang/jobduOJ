/*********************************1109************************************
题目描述：
    给定一个无向图和其中的所有边，判断这个图是否所有顶点都是连通的。
输入：
    每组数据的第一行是两个整数 n 和 m（0<=n<=1000）。n 表示图的顶点数目，
    m 表示图中边的数目。如果 n 为 0 表示输入结束。随后有 m 行数据，每行有
    两个值 x 和 y（0<x, y <=n），表示顶点 x 和 y 相连，顶点的编号从 1 开始
    计算。输入不保证这些边是否重复。
输出：
    对于每组输入数据，如果所有顶点都是连通的，输出"YES"，否则输出"NO"。
样例输入：
4 3
1 2
2 3
3 2
3 2
1 2
2 3
0 0
样例输出：
NO
YES
**************************************************************************/

#include <stdio.h>

int tree[1002];

int findroot(int x){
	if(tree[x] == -1)
		return x;
	else{
		int temp = findroot(tree[x]);
		tree[x] = temp;
		return temp;
	}
}

int main(){
	int n, m, x, y;
	int i, a, b, ans;
	while(scanf("%d %d", &n, &m) != EOF){
		if(n == 0)
			break;
		for(i=0; i<1002; i++)
			tree[i] = -1;
		while(m-- != 0){
			scanf("%d %d", &x, &y);
			a = findroot(x);
			b = findroot(y);
			if(a != b)
				tree[b] = a;
		}
		ans = 0;
		for(i=1; i<=n; i++)
			if(tree[i] == -1)
				ans++;
		if(ans == 1)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
