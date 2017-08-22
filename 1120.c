/*********************************1120************************************
题目描述：
给定一个由不同的小写字母组成的字符串，输出这个字符串的所有全排列。
我们假设对于小写字母有'a' < 'b' < ... < 'y' < 'z'，而且给定的字符串中的字
母已经按照从小到大的顺序排列。
输入：
输入只有一行，是一个由不同的小写字母组成的字符串，已知字符串的长度在1到6之间。
输出：
输出这个字符串的所有排列方式，每行一个排列。要求字母序比较小的排列在前面。
字母序如下定义：
已知S = s1s2...sk , T = t1t2...tk，则S < T 等价于，存在p (1 <= p <= k)，使得
s1 = t1, s2 = t2, ..., sp - 1 = tp - 1, sp < tp成立。
样例输入：
abc
样例输出：
abc
acb
bac
bca
cab
cba
提示：
每组样例输出结束后要再输出一个回车。
**************************************************************************/

#include <stdio.h>
#include <string.h>

char s[7];
int mark[7];
char out[7];
int len;

void F(int m){
	int i;
	if(m == len)
		printf("%s\n", out);
	else{
		for(i=0; i<len; i++){
			if(mark[i] == 0){
				mark[i] = 1;
				out[m] = s[i];
				F(m+1);
				mark[i] = 0;
			}
		}
	}
}

int main(){
	int i, j;
	char c;
	while(scanf("%s", s) != EOF){
		len = strlen(s);
		for(i=0; i<7; i++){
			out[i] = '\0';
			mark[i] = 0;
		}
		for(i=0; i<len; i++)
			for(j=0; j<len-1-i; j++)
				if(s[j] > s[j+1]){
					c = s[j];
					s[j] = s[j+1];
					s[j+1] = c;
				}
		F(0);
		printf("\n");
	}

	return 0;
}
