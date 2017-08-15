/*********************************1445************************************
题目描述：
Today is Ignatius' birthday. He invites a lot of friends. Now it's dinner
time. Ignatius wants to know how many tables he needs at least. You have 
to notice that not all the friends know each other, and all the friends 
do not want to stay with strangers.
One important rule for this problem is that if I tell you A knows B, and 
B knows C, that means A, B, C know each other, so they can stay in one table.
For example: If I tell you A knows B, B knows C, and D knows E, so A, B, C 
can stay in one table, and D, E have to stay in the other one. So Ignatius 
needs 2 tables at least.
输入：
The input starts with an integer T(1<=T<=25) which indicate the number of
test cases. Then T test cases follow. Each test case starts with two 
integers N and M(1<=N,M<=1000). N indicates the number of friends, the 
friends are marked from 1 to N. Then M lines follow. Each line consists 
of two integers A and B(A!=B), that means friend A and friend B know each 
other. There will be a blank line between two cases.
输出：
For each test case, just output how many tables Ignatius needs at least.
Do NOT print any blanks.
样例输入：
2
5 3
1 2
2 3
4 5

5 1
2 5
样例输出：
2
4
**************************************************************************/

#include <stdio.h>

int tree[1002];

int findroot(int x){
	if(tree[x] == -1)
		return x;
	else{
		int tmp = findroot(tree[x]);
		tree[x] = tmp;
		return tmp;
	}
}

int main(){
	int T, N, M;
	int k, i, x, y, a, b, ans;
	while(scanf("%d", &T) != EOF){
		for(k=0; k<T; k++){
			for(i=0; i<1002; i++)
				tree[i] = -1;
			scanf("%d %d", &N, &M);
			while(M-- != 0){
				scanf("%d %d", &x, &y);
				a = findroot(x);
				b = findroot(y);
				if(a != b)
					tree[b] = a;
			}
			ans = 0;
			for(i=1; i<=N; i++)
				if(tree[i] == -1)
					ans++;
			printf("%d\n", ans);
		}
	}

	return 0;
}
