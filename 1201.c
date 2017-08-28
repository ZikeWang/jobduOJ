/*********************************1201************************************
题目描述：
    输入一系列整数，建立二叉排序数，并进行前序，中序，后序遍历。
输入：
    输入第一行包括一个整数n(1<=n<=100)。
    接下来的一行包括n个整数。
输出：
    可能有多组测试数据，对于每组数据，将题目所给数据建立一个二叉排序树，并
    对二叉排序树进行前序、中序和后序遍历。每种遍历结果输出一行。每行最后一
    个数据之后有一个空格。
样例输入：
5
1 6 5 9 8
样例输出：
1 6 5 9 8 
1 5 6 8 9 
5 8 9 6 1 
提示：
输入中可能有重复元素，但是输出的二叉树遍历序列中重复元素不用输出。
**************************************************************************/

#include <stdio.h>

int array[101];
int loc;

typedef struct Tree{
	int value;
	struct Tree *lchild;
	struct Tree *rchild;
}TREE;

TREE tree[101];

TREE* creat(int v){
	tree[loc].value = v;
	tree[loc].lchild = NULL;
	tree[loc].rchild = NULL;
	return &tree[loc++];
}

/*TREE* build(TREE *T, int v){
	if(v < T->value){
		if(T->lchild == NULL){
			TREE *tmp = creat(v);
			T -> lchild = tmp;
		}
		else
			T -> lchild = build(T->lchild, v);
	}
	else if(v > T->value){
		if(T->rchild == NULL){
			TREE *tmp = creat(v);
			T -> rchild = tmp;
		}
		else
			T -> rchild = build(T->rchild, v);
	}
	return T;
}*/

TREE* build(TREE *T, int v){
	if(T == NULL){
		T = creat(v);
		return T;
	}
	else{
		if(v < T->value)
			T -> lchild = build(T->lchild, v);
		else if(v > T->value)
			T -> rchild = build(T->rchild, v);
		return T;
	}
}

void preOrder(TREE *T){
	printf("%d ", T->value);
	if(T -> lchild != NULL)
		preOrder(T->lchild);
	if(T -> rchild != NULL)
		preOrder(T->rchild);
}

void inOrder(TREE *T){
	if(T -> lchild != NULL)
		inOrder(T->lchild);
	printf("%d ", T->value);
	if(T -> rchild != NULL)
		inOrder(T->rchild);
}

void postOrder(TREE *T){
	if(T -> lchild != NULL)
		postOrder(T->lchild);
	if(T -> rchild != NULL)
		postOrder(T->rchild);
	printf("%d ", T->value);
}

int main(){
	int n;
	int i;
	while(scanf("%d", &n) != EOF){
		loc = 0;
		for(i=0; i<n; i++)
			scanf("%d", array+i);
		TREE *root = creat(array[0]);
		for(i=1; i<n; i++)
			root = build(root, array[i]);
		preOrder(root);printf("\n");
		inOrder(root);printf("\n");
		postOrder(root);printf("\n");
	}
	return 0;
}

/***************************************************************
这道题的代码的提交过程中出现了多次runtime error的问题，问题的关
键在于line 104和line 42~60。
1.line 42是对全局变量的初始化，在两次提交过程中（两次都是使用
line 62~74的build()函数而非line 42~60的build()函数），前一次提
交没有line 42的初始化代码，提交显示runtime error，后一次提交加上
了loc=0这一初始化步骤提交就通过了，因此在以后的代码中，（虽然全
局数值变量的缺省初始值为0，但其与编译环境等因素有关），保险起见，
在使用前均要做初始化处理。
2.build()函数的第一个版本，即line 42~60的代码在逻辑设计上出现了
漏洞，具体来说是由于判断条件的先后顺序出现问题从而导致有些情况
不能得到相应的处理。在line 42~60的代码中，是根据当前结点的value
值与要比较的值的大小进行分支处理，进而进行递归等操作然后返回。这
里就漏掉了传入的当前结点T不存在，即上一步中递归调用build()函数时
传入的参数T->lchild或T->rchild是NULL的情况。所以修正后如Line 62
~74所示，首先应该根据结点是否为NULL来做一次分支，如果非空再比较
大小从而进行第二次分支处理。
****************************************************************/