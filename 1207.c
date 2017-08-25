/*********************************1207************************************
题目描述：
求正整数N(N>1)的质因数的个数。
相同的质因数需要重复计算。如120=2*2*2*3*5，共有5个质因数。
输入：
可能有多组测试数据，每组测试数据的输入是一个正整数N，(1<N<10^9)。
输出：
对于每组数据，输出N的质因数的个数。
样例输入：
120
样例输出：
5
提示：
注意：1不是N的质因数；若N为质数，N是N的质因数。
**************************************************************************/

#include<stdio.h>  
#define M 100000  
int prime[M];  
int flag[M];  
int cnt;  
void getprime(){  
    cnt=1;  
    for(int i=2;i<M;++i)  
    {  
        if(!flag[i])  
        {  
            prime[cnt++]=i;  
            for(int j=i;j<M;j+=i)  
                flag[j]=1;  
        }  
    }  
}  
int main( )  
{ 
    int num;  
    getprime();  
    while(scanf("%d",&num)!=EOF)  
    {  
        int ans=0;  
        int i;  
        for(i=1;i<cnt;++i){  
            while(num%prime[i]==0){  
                ans++;  
                num/=prime[i];  
            }  
            if(num==1)break;  
        }  
        if(i==cnt)  
           ans++;  
        printf("%d\n",ans);  
    }  
    return 0;  
} 