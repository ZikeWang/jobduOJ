/***********************************************************************************************
*题目描述：                                                                                    *
*    有N个学生的数据，将学生数据按成绩高低排序，如果成绩相同则按姓名字符的字母序排序，         *
*    如果姓名的字母序也相同则按照学生的年龄排序，并输出N个学生排序后的信息。                   *
*输入：                                                                                        *
*    测试数据有多组，每组输入第一行有一个整数N（N<=1000），接下来的N行包括N个学生的数据。      *
*    每个学生的数据包括姓名（长度不超过100的字符串）、年龄（整形数）、成绩（小于等于100的正数）*。
*输出：                                                                                        *
*    将学生信息按成绩进行排序，成绩相同的则按姓名的字母序进行排序。                            *
*    然后输出学生信息，按照如下格式：                                                          *
*    姓名 年龄 成绩                                                                            *
*样例输入：																					   *
*3                                                                                             *
*abc 20 99                                                                                     *
*bcd 19 97                                                                                     *
*bed 20 97                                                                                     *
*样例输出：                                                                                    *
*bcd 19 97                                                                                     *
*bed 20 97                                                                                     *
*abc 20 99                                                                                     *
*提示：                                                                                        *
*学生姓名的字母序区分字母的大小写，如A要比a的字母序靠前(因为A的ASC码比a的ASC码要小)。          *
************************************************************************************************/

#include <stdio.h>
#include <string.h>

struct student
{
	char name[101];
	int age;
	int score;
}info[1000];

void swap(int i, int j){
	char tmp_name[101];
	int tmp_age, tmp_score;
	strcpy(tmp_name, info[i].name);
	strcpy(info[i].name, info[j].name);
	strcpy(info[j].name, tmp_name);
	tmp_age = (info+i)->age;
	tmp_score = (info+i)->score;
	(info+i)->age = (info+j)->age;
	(info+i)->score = (info+j)->score;
	(info+j)->age = tmp_age;
	(info+j)->score = tmp_score;
}

int main(void){
	int N;
	while(scanf("%d", &N) != EOF){
		int i, j;
		for(i=0; i<N; i++){
			scanf("%s %d %d", info[i].name, &info[i].age, &info[i].score);
		}
		for(i=0; i<N; i++)
			for(j=0; j<N-1-i; j++){
				if(info[j].score > info[j+1].score){
					swap(j, j+1);
				}
				else if(info[j].score == info[j+1].score){
					if( strcmp(info[j].name, info[j+1].name) > 0 ){
						swap(j, j+1);
					}
					else if( strcmp(info[j].name, info[j+1].name) == 0 ){
						if(info[j].age > info[j+1].age){
							swap(j, j+1);
						}
					}
				}
			}
		for(i=0; i<N; i++){
			printf("%s %d %d\n", info[i].name, info[i].age, info[i].score);
		}
	}
	return 0;
}

/*******************************************************************
 *hello.c: In function 'main':                                     *
 *hello.c:15:21: error: expected expression before 'info'          *
 *   scanf("%s %d %d", info[i].name, &info[i].age, &info[i].score);*
 *                     ^                                           * 
 *hello.c:18:22: error: expected expression before 'info'          *
 *   printf("%s %d %d", info[i].name, info[i].age, info[i].score); *
 *                                                                 *
 *出现错误是由于在定义结构体时使用的是typedef struct student{},将  *
 *typedef关键字去掉即可。                                          *
 *******************************************************************/

/*******************************************************************
 *前两次提交失败（Wrong Answer）的问题在于没有注意到题目中要求的条 *
 *件：测试数据有多组，每组输入第一行……；对于含有多组测试数据的程序 *
 *应该使用 while( scanf()!=EOF ){} 来进行循环。前两次提交的程序中没*
 *有使用到该结构，因此程序在读入一组数据后就结束了，不满足条件，WA *
 *******************************************************************/
