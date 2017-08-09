/**********1124***********************************************************
题目描述：
    The digital root of a positive integer is found by summing the digits 
    of the integer. If the resulting value is a single digit then that 
    digit is the digital root. If the resulting value contains two or 
    more digits, those digits are summed and the process is repeated. 
    This is continued as long as necessary to obtain a single digit.

    For example, consider the positive integer 24. Adding the 2 and 
    the 4 yields a value of 6. Since 6 is a single digit, 6 is the 
    digital root of 24. Now consider the positive integer 39. Adding 
    the 3 and the 9 yields 12. Since 12 is not a single digit, the 
    process must be repeated. Adding the 1 and the 2 yeilds 3, a single 
    digit and also the digital root of 39.
输入：
    The input file will contain a list of positive integers, one per line. 
    The end of the input will be indicated by an integer value of zero.
输出：
    For each integer in the input, output its digital root on a separate
    line of the output.
样例输入：
24
39
0
样例输出：
6
3
提示：
The integer may consist of a large number of digits.
**************************************************************************/
#include <stdio.h>

int sum(char *s, int cnt){
	int result=0;
	int i;
	for(i=0; i<cnt; i++)
		result += ( *(s+i) - '0' );
	return result;
}

int root(char *s, int cnt){
	int tmp, new_cnt;
	int reverse;
	tmp = sum(s, cnt);
	if(tmp < 10)
		return tmp;
	else{
		reverse = 0;
		new_cnt = 0;
		while(tmp != 0){
			reverse = reverse*10 + tmp%10;
			tmp /= 10;
		}
		while(reverse != 0){
			*(s+new_cnt) = (reverse%10) + '0';
			new_cnt++;
			reverse /= 10;
		}
		return root(s, new_cnt);
	}
}

int main(void){
	int cnt, i, tmp;
	char digit[1000];
	char c;
	while( (c=getchar())-'0' != 0){
		cnt = 0;
		digit[cnt++] = c;
		while((c=getchar()) != '\n')
			digit[cnt++] = c;
		printf("%d\n", root(digit, cnt));
	}
	return 0;
}

/*******************************************************
有两点需要注意：
1.由于没有指明输入的数的可能的取值范围，因此选择使用字符
进行输入，开辟一个较大的数组，满足大整数的读入
2.按照字符操作时，由题意知无法判断计算各位和的次数，只有
满足条件即和小于10时才终止，因此选择递归的方法，终止的条
件即为跳出递归的条件
********************************************************/