/*********************************1137************************************
题目描述：
求2个浮点数相加的和
题目中输入输出中出现浮点数都有如下的形式：
P1P2...Pi.Q1Q2...Qj
对于整数部分，P1P2...Pi是一个非负整数
对于小数部分，Qj不等于0
输入：
对于每组案例，第1行是测试数据的组数n，每组测试数据占2行，分别是两个加数。
每组测试数据之间有一个空行，每行数据不超过100个字符
输出：
每组案例是n行，每组测试数据有一行输出是相应的和。
输出保证一定是一个小数部分不为0的浮点数
样例输入：
2
0.111111111111111111111111111111
0.111111111111111111111111111111

10000000.655555555555555555555555555555
1.444444444444444444444444444445
样例输出：
0.222222222222222222222222222222
10000002.1
**************************************************************************/

#include <stdio.h>
#include <string.h>

char str[101];
char str1[101];
char str2[101];
char str3[101];
char str4[101];
int s1[101];
int s2[101];
int ri[101];
int rf[101];

void init(){
	int i;
	for(i=0; i<101; i++){
		str[i] = '\0';
		str1[i] = '\0';
		str2[i] = '\0';
		str3[i] = '\0';
		str4[i] = '\0';
		s1[i] = 0;
		s2[i] = 0;
		ri[i] = 0;
		rf[i] = 0;
	}
}

int main(void){
	int N;
	int k, i;
	int len, len1, len2, len3, len4, sl1, sl2, lf, li, tmp, fcarry;
	scanf("%d", &N);
	for(k=0; k<N; k++){
		init();
		len = len1 = len2 = len3 = len4 = sl1 = sl2 = lf = li = tmp = fcarry = 0;
		scanf("%s", str);
		len = strlen(str);
		for(i=0; i<len; i++){
			if(str[i] == '.'){
				strncpy(str1, str, i);
				strncpy(str2, str+i+1, len-i-1);
			}
		}
		scanf("%s", str);
		len = strlen(str);
		for(i=0; i<len; i++){
			if(str[i] == '.'){
				strncpy(str3, str, i);
				strncpy(str4, str+i+1, len-i-1);
			}
		}

		len1 = strlen(str1);
		len2 = strlen(str2);
		len3 = strlen(str3);
		len4 = strlen(str4);

		if(len2 > len4){
			for(i=len4; i<len2; i++)
				str4[i] = '0';
			len4 = strlen(str4);
		}
		else if(len2 < len4){
			for(i=len2; i<len4; i++)
				str2[i] = '0';
			len2 = strlen(str2);
		}

		fcarry = 0;
		for(i=len2-1; i>=0; i--){
			tmp = str2[i]-'0' + str4[i]-'0' + fcarry;
			fcarry = tmp / 10;
			tmp %= 10;
			rf[i] = tmp;
		}
		lf = len2;

		sl1 = 0;
		for(i=len1-1; i>=0; i--)
			s1[sl1++] = str1[i] - '0';
		sl2 = 0;
		for(i=len3-1; i>=0; i--)
			s2[sl2++] = str3[i] - '0';

		if(sl1 >= sl2){
			for(i=sl2; i<sl1; i++)
				s2[i] = 0;
			li = sl1;
		}
		else{
			for(i=sl1; i<sl2; i++)
				s1[i] = 0;
			li = sl2;
		}

		for(i=0; i<li; i++){
			tmp = s1[i] + s2[i] + fcarry;
			fcarry = tmp / 10;
			tmp %= 10;
			ri[i] = tmp;
		}
		if(fcarry){
			ri[i] = fcarry;
			li++;
		}

		for(i=li-1; i>=0; i--)
			printf("%d", ri[i]);
		printf(".");
		for(i=len2-1; i>=0; i--){
			if(rf[i] == 0)
				lf--;
			else
				break;
		}
		for(i=0; i<lf; i++)
			printf("%d", rf[i]);
		
		printf("\n");
	}
	return 0;
}

/******************************error********************************
#include <stdio.h>
#include <string.h>

char str[101];
char str1[101];
char str2[101];
char str3[101];
char str4[101];
int fcarry;

struct bigint{
	int digit[100];
	int size;
}big[6];

void init(){
	int i, j;
	fcarry = 0;
	for(i=0; i<101; i++){
		str[i] = '\0';
		str1[i] = '\0';
		str2[i] = '\0';
		str3[i] = '\0';
		str4[i] = '\0';
	}
	for(i=0; i<6; i++){
		big[i].size = 0;
		for(j=0; j<100; j++)
			big[i].digit[j] = 0;
	}
}

void set(char *str, int i, int len){
	int j;
	int k = 0;
	int q = 1;
	int sum = 0;

	for(j=len-1; j>=0; j--){
		sum += (str[j] - '0')*q;
		k++;
		q *= 10;
		if(k==4 || j==0){
			//printf("sum=%d; size=%d\n", sum, big[i].size);
			big[i].digit[big[i].size++] = sum;
			k = 0;
			q = 1;
			sum = 0;
		}
	}
}

void fadd(int count){
	int i;
	int tmp;
	fcarry = 0;
	for(i=0; i<big[1].size; i++){
		if(i == big[1].size-1){
			tmp = big[1].digit[i] + big[3].digit[i] + fcarry;
			fcarry = tmp  / count;
			//printf("fcarry = %d\n", fcarry);
			tmp %= count;
			//printf("tmp=%d\n", tmp);
			big[5].digit[big[5].size++] = tmp;
			break;
		}
		tmp = big[1].digit[i] + big[3].digit[i] + fcarry;
		fcarry = tmp / 10000;
		//printf("tmp = %d; fcarry = %d\n", tmp, fcarry);
		tmp %= 10000;
		big[5].digit[big[5].size++] = tmp;
	}
}

void iadd(){
	int i;
	int tmp;
	int carry = fcarry;
	for(i=0; i<big[0].size || i<big[2].size; i++){
		tmp = big[0].digit[i] + big[2].digit[i] + carry;
		carry = tmp / 10000;
		tmp %= 10000;
		big[4].digit[big[4].size++] = tmp;
	}
	if(carry)
		big[4].digit[big[4].size++] = carry;
}

int main(void){
	int N;
	int k, i, j, l, h;
	int len, len1, len2, len3, len4, l1, l2, count;
	while(scanf("%d", &N) != EOF){
	//scanf("%d", &N);
		for(i=0; i<N; i++){
			//printf("step0\n");
			init();
			//printf("step1\n");
			scanf("%s", str);
			len = strlen(str);
			//printf("str=%s; len=%d\n", str, len);
			for(l=0; l<len; l++){
				if(str[l] == '.'){
					strncpy(str1, str, l);
					strncpy(str2, str+l+1, len-l-1);
				}
			}
			//printf("str1 = %s\n", str1);
			scanf("%s", str);
			len = strlen(str);
			for(l=0; l<len; l++){
				if(str[l] == '.'){
					strncpy(str3, str, l);
					strncpy(str4, str+l+1, len-l-1);
				}
			}

			len1 = strlen(str1);
			len2 = strlen(str2);
			len3 = strlen(str3);
			len4 = strlen(str4);

			if(len2 > len4){
				for(l=len4; l<len2; l++)
					str4[l] = '0';
				len4 = strlen(str4);
			}
			else if(len2 < len4){
				for(l=len2; l<len4; l++)
					str2[l] = '0';
				len2 = strlen(str2);
			}

			set(str1, 0, len1);
			set(str2, 1, len2);
			set(str3, 2, len3);
			set(str4, 3, len4);

			l1 = len2 % 4;
			if(l1 == 0)
				count = 10000;
			else{
				count = 1;
				for(h=0; h<l1; h++)
					count *= 10;
			}
			//printf("count = %d\n", count);
			fadd(count);
			//printf("fcarry=%d\n", fcarry);
			iadd();
			for(h=big[4].size-1; h>=0; h--){
				if(h == big[4].size-1)
					printf("%d", big[4].digit[h]);
				else
					printf("%04d", big[4].digit[h]);
			}

			printf(".");

			l2 = 0;
			for(h=0; h<=big[5].size-1; h++){
				if(big[5].digit[h] != 0)
					break;
				l2++;
			}
			if(l2 != big[5].size){
				while(big[5].digit[l2] % 10 == 0){
					big[5].digit[l2] /= 10;
					if(l2 == big[5].size-1)
						count /= 10;
				}
				for(h=big[5].size-1; h>=l2; h--){
					if(h == big[5].size-1){
						if(count == 10000)
							printf("%04d", big[5].digit[h]);
						else if( count == 1000)
							printf("%03d", big[5].digit[h]);
						else if(count == 100)
							printf("%02d", big[5].digit[h]);
						else
							printf("%01d", big[5].digit[h]);
					}
					else if(h != big[5].size-1 && h == l2)
						printf("%d", big[5].digit[h]);
					else
						printf("%04d", big[5].digit[h]);
				}
			}
			
			printf("\n");
		}
	}
	return 0;
}
********************************************************************/

/*******************************************************************
这道题在一开始的方法选择上就出了问题，error的方案就是将简单问题复杂化
********************************************************************/
