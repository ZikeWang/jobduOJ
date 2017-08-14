/*********************************1208************************************
题目描述：
    对于一个十进制数A，将A转换为二进制数，然后按位逆序排列，再转换为十进制
    数B，我们乘B为A的二进制逆序数。
    例如对于十进制数173，它的二进制形式为10101101，逆序排列得到10110101，
    其十进制数为181，181即为173的二进制逆序数。
输入：
    一个1000位(即10^999)以内的十进制数。
输出：
    输入的十进制数的二进制逆序数。
样例输入：
173
样例输出：
181
**************************************************************************/

#include <stdio.h>
#include <string.h>

char A[1000];
int A2[10000];
char B[10000];
char pow2[10000];

int main(){
	int lenA, lenA2, lenp, lenB, i, j, tmp, carry;
	while(scanf("%s", A) != EOF){
		for(i=0; i<10000; i++){
			B[i] = '0';
			pow2[i] = '0';
		}
		lenA = strlen(A);
		lenA2 = 0;
		j = 0;
		while(j < lenA){
			carry = 0;
			tmp = 0;
			for(j=0; j<lenA; j++)
				if(A[j] != '0')
					break;
			for(i=j; i<lenA; i++){
				tmp = A[i]-'0' + carry * 10;
				A[i] = tmp / 2 + '0';
				carry = tmp % 2;
			}
			A2[lenA2++] = carry;
		}
		lenA2 -= 1;
		pow2[0] = 1 + '0';
		lenp = 1;
		B[0] = '0';
		lenB = 1;
		for(i=lenA2-1; i>=0; i--){
			carry = 0;
			if(A2[i] != 0){
				for(j=0; j<lenp || j<lenB; j++){
					tmp = B[j]-'0' + pow2[j]-'0' + carry;
					carry = tmp / 10;
					B[j] = tmp % 10 + '0';
				}
				if(carry){
					B[j] = carry + '0';
					lenB = j+1;
				}
				else
					lenB = j;
			}
			carry = 0;
			for(j=0; j<lenp; j++){
				tmp = pow2[j]-'0' + pow2[j]-'0' + carry;
				carry = tmp / 10;
				pow2[j] = tmp % 10 + '0';
			}
			if(carry){
				pow2[j] = carry + '0';
				lenp = j + 1;
			}
			else
				lenp = j;
		}
		for(i=lenB-1; i>=0; i--)
			printf("%c", B[i]);
		printf("\n");
	}
	return 0;
}
