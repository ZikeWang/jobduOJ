/*********************************1198************************************
题目描述：
实现一个加法器，使其能够输出a+b的值。
输入：
输入包括两个数a和b，其中a和b的位数不超过1000位。
输出：
可能有多组测试数据，对于每组数据，
输出a+b的值。
样例输入：
2 6
10000000000000000000 10000000000000000000000000000000
样例输出：
8
10000000000010000000000000000000
**************************************************************************/

#include <stdio.h>
#include <string.h>

char str1[1001];
char str2[1001];
int result[1010];

int add(int len){
	int carry = 0;
	int i, tmp;
	for(i=0; i<len; i++){
		tmp = str1[i]-'0' + str2[i]-'0' + carry;
		carry = tmp / 10;
		result[i] = tmp % 10;
	}
	if(carry){
		result[i] = carry;
		len++;
	}
	return len;
}

int main(){
	int i, len, len1, len2;
	char tmp;
	while(scanf("%s %s", str1, str2) != EOF){
		len1 = strlen(str1);
		len2 = strlen(str2);
		for(i=0; i<len1/2; i++){
			tmp = str1[i];
			str1[i] = str1[len1-1-i];
			str1[len1-1-i] = tmp;
		}
		for(i=0; i<len2/2; i++){
			tmp = str2[i];
			str2[i] = str2[len2-1-i];
			str2[len2-1-i] = tmp;
		}
		if(len1 > len2){
			for(i=len2; i<len1; i++)
				str2[i] = '0';
			len = len1;
		}
		else if(len1 < len2){
			for(i=len1; i<len2; i++)
				str1[i] = '0';
			len = len2;
		}
		else
			len = len1;
		len = add(len);
		for(i=len-1; i>=0; i--)
			printf("%d", result[i]);
		printf("\n");
	}
	return 0;
}

//要使用的变量其值不能悬空，Line 66 67是后来添加上去的，否则当len1==len2时
//line 55~64 不会执行导致len值悬空，在line 67调用函数时出错