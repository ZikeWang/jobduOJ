/*********************************1184************************************
题目描述：
编一个程序，读入用户输入的一串先序遍历字符串，根据此字符串建立一个二叉树
（以指针方式存储）。
例如如下的先序遍历字符串：
ABC##DE#G##F###
其中“#”表示的是空格，空格字符代表空树。建立起此二叉树以后，再对二叉树进行
中序遍历，输出遍历结果。
输入：
输入包括1行字符串，长度不超过100。
输出：
可能有多组测试数据，对于每组数据，
输出将输入字符串建立二叉树后中序遍历的序列，每个字符后面都有一个空格。
每个输出结果占一行。
样例输入：
abc##de#g##f###
样例输出：
c b e g d f a
**************************************************************************/

#include <stdio.h>
#include <string.h>

int loc;

typedef struct Node{
	struct Node *lchild;
	struct Node *rchild;
	char c;
}Tree;

Tree tree[101];

void inorder(Tree *T){
	if(T -> lchild != NULL)
		inorder(T->lchild);
	printf("%c ", T->c);
	if(T -> rchild != NULL)
		inorder(T->rchild);
}

Tree* creat(char *s, int index){
	tree[loc].lchild = NULL;
	tree[loc].rchild = NULL;
	tree[loc].c = s[index];
	return &tree[loc++];
}

Tree* build(char *s, int *index, int len){
	if(len==0 || *index==len || s[*index]=='#')
		return NULL;
	Tree *T = creat(s, *index);
	(*index)++;
	T -> lchild = build(s, index, len);
	(*index)++;
	T -> rchild = build(s, index, len);
	return T;
}

int main(){
	char s[101];
	int i, len, index;
	while(scanf("%s", s) != EOF){
		len = strlen(s);
		index = 0;
		Tree *root = build(s, &index, len);
		inorder(root);
		printf("\n");
	}
	return 0;
}

/*
#include <stdio.h>
#include <string.h>

int loc;

typedef struct Node{
	struct Node *lchild;
	struct Node *rchild;
	char c;
}*Tree;

Tree tree[101];

void inorder(Tree T){
	if(T -> lchild != NULL)
		inorder(T->lchild);
	printf("%c ", T->c);
	if(T -> rchild != NULL)
		inorder(T->rchild);
}

Tree creat(char *s, int index){
	tree[loc]->lchild = NULL;
	tree[loc]->rchild = NULL;
	tree[loc]->c = s[index];
	return tree[loc++];
}

Tree build(char *s, int *index, int len){
	if(len==0 || *index==len || s[*index]=='#')
		return NULL;
	Tree T = creat(s, *index);
	(*index)++;
	T -> lchild = build(s, index, len);
	(*index)++;
	T -> rchild = build(s, index, len);
	return T;
}

int main(){
	char s[101];
	int i, len, index;
	while(scanf("%s", s) != EOF){
		len = strlen(s);
		index = 0;
		Tree root = build(s, &index, len);
		inorder(root);
		printf("\n");
	}
	return 0;
}
*/

/***************************************************************
注释部分为错误的代码，错误代码与正确代码的区别在于tree[101]数组
的定义，正确代码中tree数组为结构体数组，也即数组的大小为101个结
构体的大小，因此后面在creat函数中可以直接使用数组下标的方式来使
用结构体。而在错误的代码中，tree[101]被定义成了指针数组，即数组
内的元素为指针，因此代码中并没有为每一个结点的结构体分配空间，
因此如果在creat函数中直接使用tree数组的元素指向结构体中的域将会
出现错误，修改的办法就是在creat函数中，Line 96之前，首先分配一个
结构体的结点，然后用tree中的元素指向这个结点，具体的语句就是：
tree[loc] = (Tree)malloc(sizeof(struct Node));
同时，还应在代码头部添加头文件的引用#include <malloc.h>

对于二叉树的建立操作，通常来讲要使用递归进行比较方便，另外有一处
细节需要注意的是，对于index变量（指示当前读取的字符在输入字符串
中的位置）采用的是传址而非传值，这是因为在递归的每一层中，当index
增加后，所有递归层中的index都应更新，否则如果使用传值的话，某一结
点的左右子结点处理完成后，回到上一层父结点，那么index值是父结点层
的旧值，就会重复读入已经录入的字符值从而引起错误
*****************************************************************/
