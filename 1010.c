/********************************1010*************************************
题目描述：
读入两个小于100的正整数A和B,计算A+B.
需要注意的是:A和B的每一位数字由对应的英文单词给出.
输入：
测试输入包含若干测试用例,每个测试用例占一行,格式为"A + B =",相邻两字符串有
一个空格间隔.当A和B同时为0时输入结束,相应的结果不要输出.
输出：
对每个测试用例输出1行,即A+B的值.
样例输入：
one + two =
three four + five six =
zero seven + eight nine =
zero + zero =
样例输出：
3
90
96
**************************************************************************/

#include <stdio.h>
#include <string.h> 

char numbers[10][20] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine" 
};

int main() {
	char s[100];
	char s1[50], s2[50];
	char *tmp;
	int i, j, pos1, pos2, len, l1, l2, d1, d2, a, b;
	while(gets(s)){
		len = strlen(s);
		for(i=0; i<len; i++){
			if(s[i] == '+')
				pos1 = i;
			if(s[i] == '=')
				pos2 = i;
		}
				
		for(i=0; i<=pos1-2; i++)
			s1[i] = s[i];
		s1[pos1-1] = '\0';
		l1 = strlen(s1);
		
		for(i=pos1+2; i<=pos2-2; i++)
			s2[i-pos1-2] = s[i];
		s2[pos2-1-pos1-2] = '\0';
		l2 = strlen(s2);
		
		for(i=0; i<l1; i++){
			if(s1[i] == ' '){
				d1 = 2;
				break;
			}
		}
		if(i == l1)
			d1 = 1;
			
		for(i=0; i<l2; i++){
			if(s2[i] == ' '){
				d2 = 2;
				break;
			}
		}
		if(i == l2)
			d2 = 1;
			
		if(d1==1 && d2==1 && strcmp(s1, numbers[0])==0 && strcmp(s2, numbers[0])==0)
			break;
				
		if(d1 == 1){
			for(i=0; i<10; i++){
				if(strcmp(s1, numbers[i]) == 0){
					a = i;
					break;
				}
			}
		}
		
		if(d2 == 1){
			for(i=0; i<10; i++){
				if(strcmp(s2, numbers[i]) == 0){
					b = i;
					break;
				}
			}
		}
		
		if(d1 == 2){
			tmp = strtok(s1, " ");
			for(i=0; i<10; i++){
				if(strcmp(tmp, numbers[i]) == 0){
					a = i*10;
					break;
				}
			}
			while((tmp = strtok(NULL, " ")) != NULL){
				for(i=0; i<10; i++){
					if(strcmp(tmp, numbers[i]) == 0){
						a += i;
						break;
					}
				}
			}
		}
		
		if(d2 == 2){
			tmp = strtok(s2, " ");
			for(i=0; i<10; i++){
				if(strcmp(tmp, numbers[i]) == 0){
					b = i*10;
					break;
				}
			}
			while((tmp = strtok(NULL, " ")) != NULL){
				for(i=0; i<10; i++){
					if(strcmp(tmp, numbers[i]) == 0){
						b += i;
						break;
					}
				}
			}
		}
		
		printf("%d\n", a+b);
	}
	return 0;
}


/******************************************************************
这道题主要是要掌握strtok函数的使用方法。特别是在Line 108和Line 126
对与strtok的使用以及循环条件的判断。前面运行错误的原因就在于这一部分
出现了逻辑错误。改之前是在while条件里判断tmp!=NULL，然后再用strtok
对tmp赋值，然后继续后面的for查找，这样的话如果tmp查到字符串末尾等于
NULL以后，后面再要用tmp进行strcmp等操作就很危险了，所以把tmp的赋值
直接移到while条件语句中，达到先赋值再判断的效果。
*******************************************************************/