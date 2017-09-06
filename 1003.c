/********************************1003*************************************
题目描述：
给定两个整数A和B，其表示形式是：从个位开始，每三位数用逗号","隔开。
现在请计算A+B的结果，并以正常形式输出。
输入：
输入包含多组数据数据，每组数据占一行，由两个整数A和B组成（-10^9 < A,B < 10^9）
输出：
请计算A+B的结果，并以正常形式输出，每组数据占一行。
样例输入：
-234,567,890 123,456,789
1,234 2,345,678
样例输出：
-111111101
2346912
**************************************************************************/

#include <stdio.h>
#include <string.h>

char a[20];
char b[20];
int ans[20];

int sub(char* x, char* y, int l){
	char tmp[20];
	int i, ansl;
	for(i=0; i<l; i++)
		tmp[i] = x[i];
	ansl = 0;
	for(i=0; i<l; i++){
		if(tmp[i]!=',' && y[i]!=','){
			if(tmp[i] >= y[i])
				ans[ansl++] = tmp[i] - y[i];
			else{
				tmp[i+1] -= 1;
				ans[ansl++] = tmp[i] - y[i] + 10;
			}
		}
	}
	for(i=ansl-1; i>0; i--){
		if(ans[i] == 0)
			ansl--;
		else
			break;
	}
	return ansl;
}

int main() {
	int i, j, pa, pb, la, lb, l, carry, tmp, ansl, flag;
	char absa[20];
	char absb[20];
	while(scanf("%s %s", a, b) != EOF){
		if(a[0] == '-'){
			pa = -1;
			la = strlen(a) - 1;
			for(i=la; i>=1; i--)
				absa[la-i] = a[i];
		}
		else{
			pa = 1;
			la = strlen(a);
			for(i=la-1; i>=0; i--)
				absa[la-1-i] = a[i];
		}
		
		if(b[0] == '-'){
			pb = -1;
			lb = strlen(b) - 1;
			for(i=lb; i>=1; i--)
				absb[lb-i] = b[i];
		}
		else{
			pb = 1;
			lb = strlen(b);
			for(i=lb-1; i>=0; i--)
				absb[lb-1-i] = b[i];
		}
		
		if(la > lb){
			for(i=lb; i<la; i++)
				absb[i] = '0';
			l = la;
			flag = 1;
		}
		else if(la < lb){
			for(i=la; i<lb; i++)
				absa[i] = '0';
			l = lb;
			flag = 2;
		}
		else{
			l = la;
			for(i=l-1; i>=0; i--){
				if(absa[i] == absb[i])
					continue;
				else if(absa[i] > absb[i]){
					flag = 1;
					break;
				}
				else{
					flag = 2;
					break;
				}
			}
			if(i < 0)
				flag = 0;
		}
		if(pa * pb == 1){
			carry = 0;
			tmp = 0;
			ansl = 0;
			for(i=0; i<l; i++){
				if(absa[i] != ',' && absb[i] != ','){
					tmp = absa[i]-'0' + absb[i]-'0' + carry;
					carry = tmp / 10;
					ans[ansl++] = tmp % 10; 
				}
			}
			if(carry){
				ans[ansl++] = carry;
			}
			if(pa==-1 && pb==-1)
				printf("-");
			for(i=ansl-1; i>=0; i--)
				printf("%d", ans[i]);
			printf("\n");
		}
		else if(pa == -1 && pb == 1){
			if(flag == 0){
				printf("0\n");
			}
			else if(flag == 1){
				ansl = sub(absa, absb, l);
				printf("-");
				for(i=ansl-1; i>=0; i--)
					printf("%d", ans[i]);
				printf("\n");
			}
			else if(flag == 2){
				ansl = sub(absb, absa, l);
				for(i=ansl-1; i>=0; i--)
					printf("%d", ans[i]);
				printf("\n");
			}
		}
		else if(pa == 1 && pb == -1){
			if(flag == 0){
				printf("0\n");
			}
			else if(flag == 1){
				ansl = sub(absa, absb, l);
				for(i=ansl-1; i>=0; i--)
					printf("%d", ans[i]);
				printf("\n");
			}
			else if(flag == 2){
				ansl = sub(absb, absa, l);
				printf("-");
				for(i=ansl-1; i>=0; i--)
					printf("%d", ans[i]);
				printf("\n");
			}
		}
	}
	return 0;
}
