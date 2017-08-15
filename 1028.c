/*********************************1028************************************
题目描述：
    省政府“畅通工程”的目标是使全省任何两个村庄间都可以实现公路交通（但不一
    定有直接的公路相连，只要能间接通过公路可达即可）。现得到城镇道路统计表，
    表中列出了任意两城镇间修建道路的费用，以及该道路是否已经修通的状态。现
    请你编写程序，计算出全省畅通需要的最低成本。
输入：
    测试输入包含若干测试用例。每个测试用例的第1行给出村庄数目N ( 1< N < 100 )；
    随后的 N(N-1)/2 行对应村庄间道路的成本及修建状态，每行给4个正整数，分别
    是两个村庄的编号（从1编号到N），此两村庄间道路的成本，以及修建状态：1表
    示已建，0表示未建。

    当N为0时输入结束。
输出：
    每个测试用例的输出占一行，输出全省畅通需要的最低成本。
样例输入：
3
1 2 1 0
1 3 2 0
2 3 4 0
3
1 2 1 0
1 3 2 0
2 3 4 1
3
1 2 1 0
1 3 2 1
2 3 4 1
0
样例输出：
3
1
0
**************************************************************************/

#include <stdio.h>

int tree[102];

struct road{
	int a, b;
	int len;
	int flag;
	int cost;
}road[5000];

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
	int n;
	int i, j, m, a, b, ans;
	int ta, tb, tl, tc;
	while(scanf("%d", &n) != EOF && n != 0){
		for(i=0; i<102; i++)
			tree[i] = -1;
		for(i=0; i<5000; i++){
			road[i].a = 0;
			road[i].b = 0;
			road[i].len = 0;
			road[i].flag = 0;
		}

		m = n*(n-1)/2;
		ans = 0;

		for(i=0; i<m; i++){
			scanf("%d %d %d %d", &road[i].a, &road[i].b, &road[i].len, &road[i].flag);
			road[i].cost = road[i].len * (1-road[i].flag);
		}

		for(i=0; i<m; i++)
			for(j=0; j<m-1-i; j++)
				if(road[j].cost > road[j+1].cost){
					ta = road[j].a;
					road[j].a = road[j+1].a;
					road[j+1].a = ta;

					tb = road[j].b;
					road[j].b = road[j+1].b;
					road[j+1].b = tb;

					tl = road[j].len;
					road[j].len = road[j+1].len;
					road[j+1].len = tl;

					tc = road[j].cost;
					road[j].cost = road[j+1].cost;
					road[j+1].cost = tc;
				}

		for(i=0; i<m; i++){
			a = findroot(road[i].a);
			b = findroot(road[i].b);
			if(a != b){
				tree[b] = a;
				ans += road[i].cost;
			}
		}

		printf("%d\n", ans);
	}
	return 0;
}
