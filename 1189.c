/*********************************1189************************************
题目描述：
生成一个长度为21的数组，依次存入1到21；
建立一个长度为21的单向链表，将上述数组中的数字依次存入链表每个结点中；
将上述链表变为单向封闭(循环)链表；从头结点开始数，将第17个结点删除，将它的
下一个结点作为新的头结点；重复上述过程，直到该链表中只剩一个结点，显示该结
点中存入的数字。
输入：
没有任何输入数据。
输出：
输出上面题目描述中最后剩下的节点中存入的数字。
样例输入：
样例输出：
提示：
请不要直接输出数据水过去，这样达不到提升自己的目的，
请按照题目要求来做题，这样到真正考试时才能应对自如。
**************************************************************************/

#include <stdio.h>
#include <malloc.h>

typedef struct Node{
	int num;
	struct Node *next;
}Lnode;

int main(){
	int s[21];
	int i, cnt;
	for(i=0; i<20; i++)
		s[i] = i+1;
	Lnode *head = NULL;
	Lnode *p = NULL;
	head = (Lnode*)malloc(sizeof(Lnode));
	head -> num = s[0];
	head -> next = NULL;
	Lnode *q = head;
	for(i=1; i<21; i++){
		p = (Lnode*)malloc(sizeof(Lnode));
		p -> num = s[i];
		p -> next = NULL;
		q -> next = p;
		q = p;
		if(i == 20)
			p -> next = head;
	}
	cnt = 0;
	while(cnt < 20){
		p = head;
		for(i=0; i<15; i++){
			p = p -> next;
		}
		printf("P:%d\n", p->num);
		q = p;
		q -> next = p -> next -> next;
		head = q -> next;
		printf("head:%d\n\n", head->num);
		if(head -> next == head)
			printf("%d\n", head->num);
		cnt++;
	}
	return 0;
}

//在OJ上提交时一定要先检查是否有将调试时添加的代码注释掉