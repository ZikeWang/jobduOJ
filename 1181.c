/*********************************1181************************************
题目描述：
建立一个升序链表并遍历输出。
输入：
输入的每个案例中第一行包括1个整数：n(1<=n<=1000)，接下来的一行包括n个整数。
输出：
可能有多组测试数据，对于每组数据，
将n个整数建立升序链表，之后遍历链表并输出。
样例输入：
4
3 5 7 9
样例输出：
3 5 7 9
**************************************************************************/

/*#include <stdio.h>

int num[1001];

void swap(int i, int j){
	int tmp = num[i];
	num[i] = num[j];
	num[j] = tmp;
}

void quicksort(int start, int end){
	int i = start;
	int j = end;
	int tmp = num[i];

	if(start > end)
		return;

	while(i != j){
		while(num[j]>=tmp && j>i)
			j--;
		while(num[i]<=tmp && j>i)
			i++;
		if(j > i)
			swap(i, j);
	}

	swap(i, start);
	quicksort(start, i-1);
	quicksort(i+1, end);
}

int main(){
	int n;
	int i;
	while(scanf("%d", &n) != EOF){
		for(i=0; i<n; i++)
			scanf("%d", num+i);
		quicksort(0, n-1);
		for(i=0; i<n-1; i++)
			printf("%d ", num[i]);
		printf("%d\n", num[n-1]);
	}
	return 0;
}*/

/*******************************************************
这道题暴露出来两个问题：
1.对快排的算法掌握的不牢固：Line31、32是翻了以前的快排代
码才加上去的。对于快排函数，一定要记住进入函数后要判断起
点和终点的大小关系从而设置递归的出口。在解题中如果碰到递
归问题，一定要明确递归的的出口。
2.对链表的掌握不够熟练：虽然这一题直接使用数组排序后可以
在OJ上提交通过，但链表的操作一定要熟练。
********************************************************/

/*******************************************************
使用升序链表的操作有两种方案：
1.先建立链表然后再进行排序，最后遍历链表进行输出。根据题
中的数据量，使用冒泡排序即可。这种情况下有两种插法，后面
的代码依次演示尾插法和头插法。
2.每次读入一个数据就进行排序搜索然后插入，在读取完所有数
据后建立的链表也刚好是有序的。搜索时遍历链表如果找到某个
元素比其小，该元素的后一个元素比其大，则插入到该元素后面
即可。
********************************************************/

/*#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
	int value;
	struct Node *next;
}node;

int main(){
	int n;
	int i, v, tmp;
	node *head = NULL;
	node *p = NULL;
	node *q = NULL;
	while(scanf("%d", &n) != EOF){
		head = (node*)malloc(sizeof(node));
		head -> next = NULL;
		q = head;
		for(i=0; i<n; i++){
			scanf("%d", &v);
			p = (node*)malloc(sizeof(node));
			p -> value = v;
			p -> next = NULL;
			//q = head;
			//while(q -> next != NULL)
				//q = q -> next;
			//q -> next = p;
			q -> next = p;
			q = p;
		}
		p = head -> next;
		while(p -> next != NULL){
			q = p -> next;
			while(q != NULL){
				if(p -> value > q -> value){
					tmp = p -> value;
					p -> value = q -> value;
					q -> value = tmp;
				}
				q = q -> next;
			}
			p = p -> next;
		}
		for(p=head->next; p->next!=NULL; p=p->next)
			printf("%d ", p -> value);
		printf("%d\n", p -> value);
		//p = head -> next;
		//free(head);
		p = head;
		while(p -> next != NULL){
			q = p;
			p = p -> next;
			free(q);
		}
		free(p);
	}
	return 0;
}*/

/******************************************************
1.Line 107~110的遍历不会造成超时，Line 132~138的遍历也
不会造成超时。但这两部分均可以进行优化，优化前如注释部
分所示，优化后的代码如注释部分的后面代码所示。
2.提交时显示Time Limit Exceed的原因在于，错误的代码中
head在读取数据前分配空间，即在while循环体的外面，而在
进行第一次循环时在代码段末尾释放了head的空间，所在在后
面的循环中head是没有分配空间的，而依然会被进行操作甚至
释放空间，从而产生了错误。只需把对head分配空间的部分放
在每一次循环体中即可。
3.对于链表的创建，可以以以上代码中的格式进行创建，另外
也可以以下面方案中的方式进行创建。
*******************************************************/

/*#include <stdio.h>
#include <malloc.h>

typedef struct Node
{
	int value;
	struct Node *next;
}node;

int main(){
	int n;
	int i, v, tmp;
	node *head = NULL;
	node *p = NULL;
	node *q = NULL;
	while(scanf("%d", &n) != EOF){
		head = (node*)malloc(sizeof(node));
		head -> next = NULL;
		q = head;
		for(i=0; i<n; i++){
			scanf("%d", &v);
			p = (node*)malloc(sizeof(node));
			p -> value = v;
			//p -> next = NULL;
			//q -> next = p;
			//q = p;
			p -> next = q -> next;
			q -> next = p;

		}
		p = head -> next;
		while(p -> next != NULL){
			q = p -> next;
			while(q != NULL){
				if(p -> value > q -> value){
					tmp = p -> value;
					p -> value = q -> value;
					q -> value = tmp;
				}
				q = q -> next;
			}
			p = p -> next;
		}
		for(p=head->next; p->next!=NULL; p=p->next)
			printf("%d ", p -> value);
		printf("%d\n", p -> value);
		p = head;
		while(p -> next != NULL){
			q = p;
			p = p -> next;
			free(q);
		}
		free(p);
	}
	return 0;
}*/

/******************************************************
头插法同尾插法的区别仅仅在于代码中读取数据并往链表中插入
新结点的部分，具体来说也就是Line 183、184
*******************************************************/

#include <stdio.h>
#include <malloc.h>

typedef struct Node{
	int value;
	struct Node *next;
}Lnode, *Link;

int main(){
	int n;
	Link head = NULL;
	Link p = NULL;
	Link q = NULL;
	int i, v, tmp;
	while(scanf("%d", &n) != EOF){
		head = (Link)malloc(sizeof(Lnode));
		head -> next = NULL;
		for(i=0; i<n; i++){
			scanf("%d", &v);
			p = (Link)malloc(sizeof(Lnode));
			p -> value = v;
			q = head;
			while(q -> next != NULL){
				if(q -> next -> value > p -> value)
					break;
				else
					q = q -> next;
			}
			p -> next = q -> next;
			q -> next = p;
		}
		p = head -> next;
		while(p -> next != NULL){
			q = p;
			printf("%d ", p->value);
			p = p -> next;
			free(q);
		}
		printf("%d\n", p->value);
		free(p);
		free(head);
	}
	return 0;
}

/******************************************************
上面这段代码有两处值得注意：
1.对链表结点的结构体定义，使用Lnode是因为在分配空间时要
使用sizeof计算结构体大小，使用*Link是为了方便定义结构体
指针。
2.这段代码采用在读入的时候查找并插入到有序的位置，提交的
结果显示该方法的效率更高。
*******************************************************/