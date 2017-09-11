/*********************************1195************************************
题目描述：
    输入多行字符串，请按照原文本中的顺序输出其中最短和最长的字符串，如果最
    短和最长的字符串不止一个，请全部输出。
输入：
输入包括多行字符串，字符串的长度len,(1<=len<=1000)。
输出：
按照原文本中的顺序输出其中最短和最长的字符串，如果最短和最长的字符串不止一
个，请全部输出。
样例输入：
hello
she
sorry
he
样例输出：
he
hello
sorry
**************************************************************************/

#include <stdio.h>
#include <string.h>

struct Str{
	char s[1001];
	int len;
}str[1000];

void swap(int i, int j){
	int tmp_len = str[i].len;
	str[i].len = str[j].len;
	str[j].len = tmp_len;

	char tmp_s[1001];
	strcpy(tmp_s, str[i].s);
	strcpy(str[i].s, str[j].s);
	strcpy(str[j].s, tmp_s);
}

int main(){
	int i, j, cnt, lmin, lmax;
	cnt = 0;
	while(scanf("%s", str[cnt].s) != EOF){
		str[cnt].len = strlen(str[cnt].s);
		cnt++;
	}
	for(i=0; i<cnt; i++)
		for(j=0; j<cnt-1-i; j++)
			if(str[j].len > str[j+1].len)
				swap(j, j+1);
	lmin = str[0].len;
	lmax = str[cnt-1].len;
	for(i=0; i<cnt; i++)
		if(str[i].len == lmin || str[i].len == lmax)
			printf("%s\n", str[i].s);
	return 0;
}

//这种题目的输入方式值得注意。它是一次性输入多行案例然后到文件结尾结束。
//在调试的过程中按ctrl+z结束输入，产生的效果与EOF等效

//在排序过程中使用>或者<而非>=或<=不会影响相同大小结果的原始先后顺序
