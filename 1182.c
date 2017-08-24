/*********************************1182************************************
题目描述：
编一个程序，读入用户输入的，以“.”结尾的一行文字，统计一共有多少个单词，并
分别输出每个单词含有多少个字符。
（凡是以一个或多个空格隔开的部分就为一个单词）
输入：
输入包括1行字符串，以“.”结束，字符串中包含多个单词，单词之间以一个或多个空
格隔开。
输出：
可能有多组测试数据，对于每组数据，
输出字符串中每个单词包含的字母的个数。
样例输入：
hello how are you.
样例输出：
5 3 3 3
**************************************************************************/

#include <stdio.h>
#include <string.h>

char s[10001];
int ans[10001];

int main(){
	int i, len, flag, cnt1, cnt2;
	while(gets(s)){
		len = strlen(s);
		cnt1 = 0;
		cnt2 = 0;
		flag = 0;
		for(i=0; i<len; i++){
			if(s[i] != ' ' && i != len-1){
				flag = 1;
				cnt1++;
			}
			else{
				if(flag || i==len-1){
					ans[cnt2++] = cnt1;
					cnt1 = 0;
					flag = 0;
				}
			}
		}
		for(i=0; i<cnt2-1; i++)
			printf("%d ", ans[i]);
		printf("%d\n", ans[i]);
	}
	return 0;
}