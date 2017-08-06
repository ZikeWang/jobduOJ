/*************************************************************************
题目描述：
    Excel可以对一组纪录按任意指定列排序。现请你编写程序实现类似功能。
    对每个测试用例，首先输出1行“Case i:”，其中 i 是测试用例的编号（从1开始）。
    随后在 N 行中输出按要求排序后的结果，即：当 C=1 时，按学号递增排序；
    当 C=2时，按姓名的非递减字典序排序；当 C=3 时，按成绩的非递减排序。
    当若干学生具有相同姓名或者相同成绩时，则按他们的学号递增排序。
输入：
    测试输入包含若干测试用例。每个测试用例的第1行包含两个整数 N (N<=100000) 和 C，
    其中 N 是纪录的条数，C 是指定排序的列号。以下有N行，每行包含一条学生纪录。
    每条学生纪录由学号（6位数字，同组测试中没有重复的学号）、
    姓名（不超过8位且不包含空格的字符串）、成绩（闭区间[0, 100]内的整数）组成，
    每个项目间用1个空格隔开。当读到 N=0 时，全部输入结束，相应的结果不要输出。
输出：
    对每个测试用例，首先输出1行“Case i:”，其中 i 是测试用例的编号（从1开始）。
    随后在 N 行中输出按要求排序后的结果，即：当 C=1 时，按学号递增排序；
    当 C=2时，按姓名的非递减字典序排序；当 C=3 时，按成绩的非递减排序。
    当若干学生具有相同姓名或者相同成绩时，则按他们的学号递增排序。
样例输入：
3 1
000007 James 85
000010 Amy 90
000001 Zoe 60
4 2
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 98
4 3
000007 James 85
000010 Amy 90
000001 Zoe 60
000002 James 90
0 0
样例输出：
Case 1:
000001 Zoe 60
000007 James 85
000010 Amy 90
Case 2:
000010 Amy 90
000002 James 98
000007 James 85
000001 Zoe 60
Case 3:
000001 Zoe 60
000007 James 85
000002 James 90
000010 Amy 90
**************************************************************************/
/********bubble sort******************************************************
#include <stdio.h>
#include <string.h>

struct excel{
	char id[7];
	char name[9];
	int score;
}buf[100000];

void swap(int i, int j){
	char tmp_id[7];
	strcpy(tmp_id, buf[i].id);
	char tmp_name[9];
	strcpy(tmp_name, buf[i].name);
	int tmp_score = buf[i].score;
	strcpy(buf[i].id, buf[j].id);
	strcpy(buf[i].name, buf[j].name);
	buf[i].score = buf[j].score;
	strcpy(buf[j].id, tmp_id);
	strcpy(buf[j].name, tmp_name);
	buf[j].score = tmp_score;
}

int main(void){
	int N, cno;
	while(scanf("%d %d", &N, &cno) != EOF){
		if(N == 0)
			break;
		int i, j;
		for(i=0; i<N; i++)
			scanf("%s %s %d", buf[i].id, buf[i].name, &buf[i].score);
		switch(cno){
			case 1:
				for(i=0; i<N; i++)
					for(j=0; j<N-1-i; j++)
						if( strcmp(buf[j].id, buf[j+1].id) > 0 )
							swap(j, j+1);
				break;
			case 2:
				for(i=0; i<N; i++)
					for(j=0; j<N-1-i; j++)
						if( strcmp(buf[j].name, buf[j+1].name) > 0 )
							swap(j, j+1);
						else if( strcmp(buf[j].name, buf[j+1].name) == 0 )
							if( strcmp(buf[j].id, buf[j+1].id) > 0 )
								swap(j, j++);
				break;
			case 3:
				for(i=0; i<N; i++)
					for(j=0; j<N-1-i; j++)
						if(buf[j].score > buf[j+1].score)
							swap(j, j+1);
						else if(buf[j].score == buf[j+1].score)
							if( strcmp(buf[j].id, buf[j+1].id) > 0 )
								swap(j, j++);
				break;
		}
		printf("Case %d:\n", cno);
		for(i=0; i<N; i++)
			printf("%s %s %d\n", buf[i].id, buf[i].name, buf[i].score);
	}
	return 0;
}
**************************************************************************/

#include <stdio.h>
#include <string.h>

struct excel{
	char id[7];
	char name[9];
	int score;
}buf[100000];

void swap(int i, int j){
	char tmp_id[7];
	strcpy(tmp_id, buf[i].id);
	char tmp_name[9];
	strcpy(tmp_name, buf[i].name);
	int tmp_score = buf[i].score;
	strcpy(buf[i].id, buf[j].id);
	strcpy(buf[i].name, buf[j].name);
	buf[i].score = buf[j].score;
	strcpy(buf[j].id, tmp_id);
	strcpy(buf[j].name, tmp_name);
	buf[j].score = tmp_score;
}

void quicksort1(int left, int right){
	int i, j;
	char temp_id[7];

	if(left > right)
		return;

	strcpy(temp_id, buf[left].id);
	i = left;
	j = right;

	while(i != j){
		while( strcasecmp(buf[j].id, temp_id)>=0 && i<j )
			j--;
		while( strcasecmp(buf[i].id, temp_id)<=0 && i<j )
			i++;
		if(i < j)
			swap(i, j);
	}

	swap(left, i);
	quicksort1(left, i-1);
	quicksort1(i+1, right);
}

void quicksort2(int left, int right){
	int i, j;
	char temp_name[9];

	if(left > right)
		return;

	strcpy(temp_name, buf[left].name);
	i = left;
	j = right;

	while(i != j){
		while( strcasecmp(buf[j].name, temp_name)>=0 && i<j )
			j--;
		while( strcasecmp(buf[i].name, temp_name)<=0 && i<j )
			i++;
		if(i < j)
			swap(i, j);
	}

	swap(left, i);
	quicksort2(left, i-1);
	quicksort2(i+1, right);
}

void quicksort3(int left, int right){
	int i, j;
	int temp_score;

	if(left > right)
		return;

	temp_score = buf[left].score;
	i = left;
	j = right;

	while(i != j){
		while( buf[j].score>=temp_score && i<j )
			j--;
		while( buf[i].score<=temp_score && i<j )
			i++;
		if(i < j)
			swap(i, j);
	}

	swap(left, i);
	quicksort3(left, i-1);
	quicksort3(i+1, right);
}

int main(void){
	int N, cno;
	int count = 0;
	while(scanf("%d %d", &N, &cno) != EOF){
		if(N == 0 && cno == 0)
			break;
		int i, j, start, end;
		for(i=0; i<N; i++)
			scanf("%s %s %d", buf[i].id, buf[i].name, &buf[i].score);
		switch(cno){
			case 1:
				quicksort1(0, N-1);
				break;
			case 2:
				quicksort2(0, N-1);
				for(i=0; i<N; i++){
					start = i;
					for(j=i; j<N; j++){
						if(strcasecmp(buf[start].name, buf[j].name)==0)
							end = j;
						else
							break;
					}
					if(end > start)
						quicksort1(start, end);
				}
				break;
			case 3:
				quicksort3(0, N-1);
				for(i=0; i<N; i++){
					start = i;
					for(j=i; j<N; j++){
						if(buf[start].score==buf[j].score)
							end = j;
						else
							break;
					}
					if(end > start)
						quicksort1(start, end);
				}
				break;
		}
		printf("Case %d:\n", count++);
		for(i=0; i<N; i++)
			printf("%s %s %d\n", buf[i].id, buf[i].name, buf[i].score);
	}
	return 0;
}

/*************************************************************************
有几个地方值得注意：
1.使用冒泡排序不行是因为N的取值范围太大，冒泡排序的时间复杂度太大，会导致
在1s的时间限制内无法完成，因此选用快排
2.使用快排时在移动哨兵i、j时使用大于等于或小于等于，不带等号会导致错误
3.在排序规则2、3下，若姓名、成绩相等则使用学号排序的规则，不能将条件叠加在
快排的分治条件中。这里有两种策略，一种是本程序的先使用主要的key排序，然后
在排好序的元素中，找到key相同的，对这些连续元素再使用学号key进行快排；另一
种是先使用学号key进行快排，然后使用stable sort保证在学号key的顺序不改变的
情况下使用（姓名、成绩）key进行排序
4.注意题目要求，输出1行“Case i:”，其中 i 是测试用例的编号（从1开始），case
后面是递增的计数，而不是选用的排序规则编号
5.注意题目隐含意思，该题中姓名不区分大小写，因此排序时选用strcasecmp函数，
（linux下gcc用strcasecmp，win下可用stricmp）。对于姓名字母是否区分大小写，
不同的题目要求不同，这里不能一概而论
**************************************************************************/