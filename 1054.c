/*************************************************************************
题目描述：
输入一个字符串，长度小于等于200，然后将输出按字符顺序升序排序后的字符串。
输入：
测试数据有多组，输入字符串。
输出：
对于每组输入,输出处理后的结果。
样例输入：
bacd
样例输出：
abcd
**************************************************************************/

#include <stdio.h>
#include <string.h>

char str[200];

void swap(int i, int j){
	char temp = str[i];
	*(str+i) = *(str+j);
	*(str+j) = temp;
}

int main(void){
	while(scanf("%s", str) != EOF){
		int len = strlen(str);
		int i, j;
		for(i=0; i<len; i++)
			for(j=0; j<len-1-i; j++){
				if(str[j] > str[j+1])
					swap(j, j+1);
			}
		printf("%s\n", str);
	}
	return 0;
}

