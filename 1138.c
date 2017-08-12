/**********1138***********************************************************
题目描述：
将一个长度最多为30位数字的十进制非负整数转换为二进制数输出。
输入：
多组数据，每行为一个长度不超过30位的十进制非负整数。
（注意是10进制数字的个数可能有30个，而非30bits的整数）
输出：
每行输出对应的二进制数。
样例输入：
0
1
3
8
样例输出：
0
1
11
1000
**************************************************************************/

#include <stdio.h>
#include <string.h>

char num[32];

int devide(int *cnt){
	int left = 0;
	int curbit, lowbit;
	int i = *cnt - 1;
	if( (*cnt>1&&num[*cnt-1]-'0'==1) || (*cnt==1&&num[0]-'0'==1) )
		*cnt -= 1;
	while(i){
		curbit = num[i] - '0' + left;
		if(curbit == 1){
			*(num+i) = '0';
			left = 10;
		}
		else if(curbit%2 == 0){
			*(num+i) = curbit / 2 + '0';
			left = 0;
		}
		else if(curbit%2 == 1){
			*(num+i) = (curbit-1) / 2 + '0';
			left = 10;
		}
		i--;
	}
	lowbit = num[i] - '0' + left;
	if(lowbit == 1){
		*(num+i) = '0';
		return 1;
	}
	else if(lowbit%2 == 0){
		*(num+i) = lowbit / 2 + '0';
		return 0;
	}
	else if(lowbit%2 == 1){
		*(num+i) = (lowbit-1) / 2 + '0';
		return 1;
	}
}

int main(void){
	char tmp[31];
	int ans[1001];
	char c;
	int cnt10, cnt2, i;
	while(scanf("%s", num) != EOF){
		cnt10 = strlen(num);
		cnt2 = 0;
		if(cnt10==1 && num[0] == '0'){
			printf("0\n");
			continue;
		}
		for(i=0; i<cnt10; i++)
			tmp[i] = num[cnt10-1-i];
		for(i=0; i<cnt10; i++)
			*(num+i) = tmp[i];
		while(cnt10){
			ans[cnt2++] = devide(&cnt10);
		}
		for(i=cnt2-1; i>=0; i--)
			printf("%d", ans[i]);
		printf("\n");
	}
	return 0;
}

/*******************error*********************
int main(){
	long long int a;
	int ans[1001];
	int cnt;
	while(scanf("%lld", &a) != EOF){
		cnt = 0;
		do{
			ans[cnt++] = a % 2;
			a /= 2;
		}while(a);
		while(cnt != 0){
			printf("%d", ans[cnt-1]);
			cnt--;
		}
		printf("\n");
	}
	return 0;
}
********************************************/

/*****************新思路********************
#include <stdio.h>  
#include <string.h>  
int main()  
{  
    int num[31],i,j,yu[100];  
    char str[31];  
    while(scanf("%s",str)!=EOF)  
    {  
        for(i=0;str[i];i++)  
            num[i]=str[i]-'0';  
  
        int jie=0,len=i,j=0,temp; //000000  
        while(1)  
        {  
            i=0;  
            while(num[i]==0&&i<len)  
                i++;  
            if(i==len)  
                break;  
  
            jie=0;  
            for(;i<len;i++)  
            {  
                temp=jie*10+num[i];  
                num[i]=temp/2;  
                jie=temp%2;  
            }  
            yu[j++]=jie;  
        }  
  
        if(j==0)  
            printf("0\n");  
        else  
        {  
            for(i=j-1;i>=0;i--)  //余数逆序输出  
                printf("%d",yu[i]);  
            printf("\n");  
        }  
    }  
    return 0;  
}
********************************************/

/**************************************************************
有点需要注意：
1.本算法与新算法在原理上大同小异，都是根据除法原理从高位到低位
逐次计算。在原算法中while(i){}内的所有if-else均无必要，可以将算
num[i]的值全部统一为curbit/2+'0'（因为/运算向小方向舍余），后面
算lowbit同样可以简化为一个统一的式子lowbit/2+'0'从而不必使用繁琐
的if-else进行条件分支。另外新算法并未将输入首先做倒序的预处理，
另外其对结束条件的判断方法同样值得借鉴。
2.设计算法时要注意结束条件（如Line 30）
3.runtime error:错误时num[]数组在main()中定义。将num[]的定义放到
自定义函数前作为全局定义即可，原因未知
4.对于本题中类似的输入方法，即要读入一个字符串到数组中，并且字符
串中没有空格，可以直接使用%s读入，而不必要使用%c，getchar()一个
一个读取然后以读取到换行符'\n'结束，这样的话太复杂，在本题中还引
起了Time Limie问题，修改为读取整个字符串后即解决（例如测试用例中
不同用例间可能并不是以换行符区分，可能都在一整串输入流中，以数量
来间隔）
***************************************************************/
