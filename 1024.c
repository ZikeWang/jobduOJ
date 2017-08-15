/*********************************1024************************************
题目描述：
    省政府“畅通工程”的目标是使全省任何两个村庄间都可以实现公路交通（但不一
    定有直接的公路相连，只要能间接通过公路可达即可）。经过调查评估，得到的
    统计表中列出了有可能建设公路的若干条道路的成本。现请你编写程序，计算出
    全省畅通需要的最低成本。
输入：
    测试输入包含若干测试用例。每个测试用例的第1行给出评估的道路条数 N、村庄
    数目M (N, M < =100 )；随后的 N 行对应村庄间道路的成本，每行给出一对正整
    数，分别是两个村庄的编号，以及此两村庄间道路的成本（也是正整数）。为简单
    起见，村庄从1到M编号。当N为0时，全部输入结束，相应的结果不要输出。
输出：
    对每个测试用例，在1行里输出全省畅通需要的最低成本。若统计数据不足以保证
    畅通，则输出“?”。
样例输入：
3 3
1 2 1
1 3 2
2 3 4
1 3
2 3 2
0 100
样例输出：
3
?
**************************************************************************/

#include <stdio.h>

int tree[102];

struct road{
	int a, b;
	int len;
}road[102];

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
	int n, m;
	int i, j, start, end, length, a, b, cnt, ans, flag;
	int tmp_a, tmp_b, tmp_len;
	while(scanf("%d %d", &n, &m) != EOF && n != 0){
		cnt = 0;
		ans = 0;
		flag = 0;

		for(i=0; i<102; i++){
			tree[i] = -1;
			road[i].a = 0;
			road[i].b = 0;
			road[i].len = 0;
		}

		for(i=0; i<n; i++){
			scanf("%d %d %d", &start, &end, &length);
			road[cnt].a = start;
			road[cnt].b = end;
			road[cnt].len = length;
			cnt++;
		}

		for(i=0; i<cnt; i++)
			for(j=0; j<cnt-1-i; j++)
				if(road[j].len > road[j+1].len){
					tmp_a = road[j].a;
					road[j].a = road[j+1].a;
					road[j+1].a = tmp_a;

					tmp_b = road[j].b;
					road[j].b = road[j+1].b;
					road[j+1].b = tmp_b;

					tmp_len = road[j].len;
					road[j].len = road[j+1].len;
					road[j+1].len = tmp_len;
				}

		for(i=0; i<cnt; i++){
			a = findroot(road[i].a);
			b = findroot(road[i].b);
			if(a != b){
				tree[b] = a;
				ans += road[i].len;
			}
		}

		for(i=1; i<=m; i++)
			if(tree[i] == -1)
				flag++;

		if(flag == 1)
			printf("%d\n", ans);
		else
			printf("?\n");
	}
	return 0;
}
