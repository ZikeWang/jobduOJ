/********************************1014*************************************
题目描述：
    今天的上机考试虽然有实时的Ranklist，但上面的排名只是根据完成的题数排序，
    没有考虑每题的分值，所以并不是最后的排名。给定录取分数线，请你写程序找
    出最后通过分数线的考生，并将他们的成绩按降序打印。
输入：
    测试输入包含若干场考试的信息。每场考试信息的第1行给出考生人数N(0<N<1000)、
    考题数M ( 0 < M < = 10 )、分数线（正整数）G；第2行排序给出第1题至第M题
    的正整数分值；以下N行，每行给出一名考生的准考证号（长度不超过20的字符串）
    该生解决的题目总数m、以及这m道题的题号（题目号由1到M）。 
    当读入的考生人数为0时，输入结束，该场考试不予处理。
输出：
    对每场考试，首先在第1行输出不低于分数线的考生人数n，随后n行按分数从高
    到低输出上线考生的考号与分数，其间用1空格分隔。若有多名考生分数相同，
    则按他们考号的升序输出。
样例输入：
4 5 25
10 10 12 13 15
CS004 3 5 1 3
CS003 5 2 4 1 3 5
CS002 2 1 2
CS001 3 2 3 5
1 2 40
10 30
CS001 1 2
2 3 20
10 10 10
CS000000000000000001 0
CS000000000000000002 2 1 2
0
样例输出：
3
CS003 60
CS001 37
CS004 37
0
1
CS000000000000000002 20
**************************************************************************/

#include <stdio.h>
#include <string.h>

struct Student{
	char id[25];
	int score;
}info[1001];

void swap(int i, int j){
	char tmp_id[25];
	strcpy(tmp_id, info[i].id);
	strcpy(info[i].id, info[j].id);
	strcpy(info[j].id, tmp_id);
		
	int tmp_score = info[i].score;
	info[i].score= info[j].score;
	info[j].score = tmp_score;
}

int main() {
	int n, m, g, mark[11];
	int i, j, number, cnt, count;
	while(scanf("%d", &n) != EOF && n != 0){
		scanf("%d %d", &m, &g);
		for(i=0; i<1001; i++)
			info[i].score = 0;
		for(i=0; i<m; i++)
			scanf("%d", mark+i);
		for(i=0; i<n; i++){
			scanf("%s %d", info[i].id, &cnt);
			for(j=0; j<cnt; j++){
				scanf("%d", &number);
				info[i].score += mark[number-1];
			}
		}
		
		for(i=0; i<n; i++)
			for(j=0; j<n-1-i; j++){
				if(info[j].score < info[j+1].score){
					swap(j, j+1);
				}
				else if(info[j].score == info[j+1].score){
					if(strcmp(info[j].id, info[j+1].id) > 0)
						swap(j, j+1);
				}
			}

		count = 0;
		for(i=0; i<n; i++)
			if(info[i].score >= g)
				count++;
		if(count == 0)
			printf("0\n");
		else{
			printf("%d\n", count);
			for(i=0; i<count; i++)
				printf("%s %d\n", info[i].id, info[i].score);
		}
	}
	return 0;
}

/*********************************************************************
1.提交的过程中出现了一次runtime error和依次Time Limit Exceed
出现Runtime Error的原因在于Line 45之前定义的大小为22，而Line 50为20，
因此当id字符串过长时可能发生了越界；当将Line 50改成22后出现TLE的错误，
然后将这两处均改成25时即可，原因不明，应该和访问越界有关
2.结构体中之前还定义了保存该学生答题数量的int域和答题编号的int[]域，这
样导致swap函数比较复杂。这两个数据只在输入时计算score用到，所以完全没有
必要保存，所以在输入时用一个临时变量存储即可，可以简化代码
3.swap函数中交换时之前Line 57写成了info[j].score = info[i].score，这样
的低级错误应该避免
4.在数组赋值等操作时要注意下标的一致性，数组是从0开始的，而有些题目中
的顺序序号是从1开始的，这里就要做一个转换，Line 73的mark的下标之前就没
有注意到这个问题而直接用的number或者number+1
5.结束条件和输入函数的配合。本题的第一行正常情况应该读入3个整数，但在
输入结束时需要输入0即结束，因此在输入时应该先读取n，再读取m，g，而不应
该直接用scanf("%d %d %d")这样的格式，否则在输入n=0后还必须都两个数字才
可以结束，与题意不符
6.注意排序的顺序。Line 83之前写成了<,而题目要求的是升序
**********************************************************************/