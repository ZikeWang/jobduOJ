/*********************************1199************************************
题目描述：
对给定的一个字符串，找出有重复的字符，并给出其位置，如：abcaaAB12ab12
输出：a，1；a，4；a，5；a，10，b，2；b，11，1，8；1，12， 2，9；2，13。
输入：
输入包括一个由字母和数字组成的字符串，其长度不超过100。
输出：
可能有多组测试数据，对于每组数据，
按照样例输出的格式将字符出现的位置标出。
样例输入：
abcaaAB12ab12
样例输出：
a:0,a:3,a:4,a:9
b:1,b:10
1:7,1:11
2:8,2:12
提示：
1、下标从0开始。
2、相同的字母在一行表示出其出现过的位置。
**************************************************************************/

#include <stdio.h>
#include <string.h>

char s[101];

struct COUNT{
	char c;
	int cnt;
	int no[101];
}count[101];

int main(){
	int i, j, len, num, flag;
	while(scanf("%s", s) != EOF){
		len = strlen(s);
		for(i=0; i<len; i++){
			count[i].cnt = 0;
		}
		num = 0;
		for(i=0; i<len; i++){
			flag = 0;
			for(j=0; j<num; j++){
				if(count[j].c == s[i]){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				count[num].c = s[i];
				count[num].no[count[num].cnt++] = i;
				num++;
			}
			else{
				count[j].no[count[j].cnt++] = i;
			}
		}
		for(i=0; i<num; i++){
			if(count[i].cnt > 1){
				for(j=0; j<count[i].cnt-1; j++)
					printf("%c:%d,", count[i].c, count[i].no[j]);
				printf("%c:%d\n", count[i].c, count[i].no[j]);
			}
		}
	}
	return 0;
}