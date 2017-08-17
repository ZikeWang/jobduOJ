/*********************************1446************************************
题目描述：
One way that the police finds the head of a gang is to check people's phone 
calls. If there is a phone call between A and B, we say that A and B is 
related. The weight of a relation is defined to be the total time length 
of all the phone calls made between the two persons. A "Gang" is a cluster
of more than 2 persons who are related to each other with total relation 
weight being greater than a given threthold K. In each gang, the one with
maximum total weight is the head. Now given a list of phone calls, you 
are supposed to find the gangs and the heads.
输入：
For each case, the first line contains two positive numbers N and K (both
 less than or equal to 1000), the number of phone calls and the weight 
 threthold, respectively. Then N lines follow, each in the following format:
Name1 Name2 Time
where Name1 and Name2 are the names of people at the two ends of the call, 
and Time is the length of the call. A name is a string of three capital 
letters chosen from A-Z. A time length is a positive integer which is no 
more than 1000 minutes.
输出：
For each test case, first print in a line the total number of gangs. Then 
for each gang, print in a line the name of the head and the total number
of the members. It is guaranteed that the head is unique for each gang.
The output must be sorted according to the alphabetical order of the 
names of the heads.
样例输入：
8 59
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
8 70
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
样例输出：
2
AAA 3
GGG 3
0
**************************************************************************/

#include <stdio.h>
#include <string.h>

int sum[2002];

struct TREE{
	char name[4];
	int root;
	int len;
}tree[2002];

struct GANG{
	char gname[4];
	int gsum;
}gang[2002];

int findroot(int x){
	if(tree[x].root == -1)
		return x;
	else{
		int tmp = findroot(tree[x].root);
		tree[x].root = tmp;
		return tmp;
	}
}

int main(){
	int n, k;
	int i, j, l, cnt, length, a, b, total, max, no, gcnt, tmp_gsum, tmp_root;
	char str1[4], str2[4], tmp_gname[4];
	while(scanf("%d %d", &n, &k) != EOF){
		for(i=0; i<2002; i++){
			sum[i] = 1;
			tree[i].root = -1;
			tree[i].len = 0;
			gang[i].gsum = 0;
			for(j=0; j<4; j++){
				tree[i].name[j] = '\0';
				gang[i].gname[j] = '\0';
			}
		}
		cnt = 0;
		i = 0;
		j = 0;
		while(n-- != 0){
			scanf("%s %s %d", str1, str2, &length);
			for(i=0; i<cnt; i++){
				if(strcmp(str1, tree[i].name) == 0){
					tree[i].len += length;
					break;
				}
			}
			if(i == cnt){
				strcpy(tree[i].name, str1);
				tree[i].len = length;
				cnt++;
			}
			for(j=0; j<cnt; j++){
				if(strcmp(str2, tree[j].name) == 0){
					tree[j].len += length;
					break;
				}
			}
			if(j == cnt){
				strcpy(tree[j].name, str2);
				tree[j].len = length;
				cnt++;
			}
			a = findroot(i);
			b = findroot(j);
			//printf("%d %d\n", a, b);
			if(a != b){
				tmp_root = tree[b].root;
				tree[b].root = a;
				if(tmp_root == -1)
					for(l=0; l<cnt; l++){
						if(tree[l].root == b)
							tree[l].root = a; 
					}
				//printf("b: sum[%d] = %d; sum[%d]=%d\n", i, sum[i], j, sum[j]);
				sum[a] += sum[b];
				//printf("a: sum[%d] = %d; sum[%d]=%d\n", i, sum[i], j, sum[j]);
			}
		}
		//printf("cnt = %d\n\n", cnt);
		//for(i=0; i<cnt; i++){
			//printf("tree[%d].name=%s; tree[%d].len=%d; tree[%d].root=%d; sum[%d]=%d\n", i, tree[i].name, i, tree[i].len, i, tree[i].root, i, sum[i]);
		//}
		//printf("\n");
		gcnt = 0;
		for(i=0; i<cnt; i++){
			if(tree[i].root == -1 && sum[i] > 2){
				total = 0;
				max = 0;
				no = 0;
				for(j=0; j<cnt; j++){
					if(tree[j].root == i || j==i){
						total += tree[j].len;
						if(tree[j].len >= max){
							max = tree[j].len;
							no = j;
						}
						//printf("i=%d; j=%d; total=%d\n", i, j, total);
					}
				}
				if(total/2 > k){
					gang[gcnt].gsum = sum[i];
					strcpy(gang[gcnt].gname, tree[no].name);
					gcnt++;
				}
			}
		}

		printf("%d\n", gcnt);

		for(i=0; i<gcnt; i++)
			for(j=0; j<gcnt-1-i; j++){
				if(strcmp(gang[j].gname, gang[j+1].gname) > 0){
					tmp_gsum = gang[j].gsum;
					gang[j].gsum = gang[j+1].gsum;
					gang[j+1].gsum = tmp_gsum;
					strcpy(tmp_gname, gang[j].gname);
					strcpy(gang[j].gname, gang[j+1].gname);
					strcpy(gang[j+1].gname, tmp_gname);
				}
			}

		for(i=0; i<gcnt; i++)
			printf("%s %d\n", gang[i].gname, gang[i].gsum);
	}
	return 0;
}

/*************************************************************
问题出在对并查集的理解不够透彻：
首先看这样一个测试用例：
9 59
AAA BBB 10
AAA CCC 40
DDD EEE 5
EEE DDD 20
FFF GGG 30
GGG HHH 20
HHH FFF 30
CCC MMM 42
GGG MMM 23

正确的结果应该是一个gang，通话时间最长的是CCC，人数为7但之前提
交的代码会错误的输出为GGG 7

问题的关键在于最后一组数据，在最后一组数据前的集合如下：
（0 1 2 8）（5 6 7）（3 4），第一个数据为root，由于函数findroot
的作用，每个集合中非根元素均为根结点的叶子结点。

最后一组数据读入后需要产生的效果就是将前两个集合合并，并将0作为
5的子结点，这一步由tree[b].root=a实现，另外计算合并后的结点总数
sum也没问题。但是要注意到，这样做只是更新了b的root值，b的叶子结
点的root值依然是b而非a，也就是说合并后的新集合（0 1 2 8 5 6 7）
并不是以5为根结点，其他节点均为叶子结点的“伞状”结构。

但是后面对每个集合进行遍历时，根据遍历条件tree[j].root == i或是
j==i可知这是按照“伞状”结构为前提进行遍历的，这种方案是假设根结
点下的所有子结点都直接跟根结点相连，因此计算中就漏掉了0的子结点

可以有两种修改方法，一种方法是如代码所示，如果修改的是根结点的
root域（即b得到的某个集合的根结点）那么就将该根结点下的所有子
结点的root域做相应的修改，从而保证集合中所有非根结点与根结点直
接相连；另一种方法是考虑到findroot函数实现的一个效果就是将当前
结点的结构调整为“伞状”的结构，但findroot函数只能从传入的x结点
开始往根结点方向向上对root域进行递归调整，也就是说它并不调整x
结点下面的子结点的root域，那么在所有结点添加、集合合并完成后保
险起见可以遍历所有结点，对每个结点使用findroot函数（不过这样做
当结点数量太大时可能会产生较大的开销）
**************************************************************/
