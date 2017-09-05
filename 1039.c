/*********************************1039************************************
题目描述：
You are given a sequence of integer numbers. Zero-complexity transposition 
of the sequence is the reverse of this sequence. Your task is to write a 
program that prints zero-complexity transposition of the given sequence.
输入：
For each case, the first line of the input file contains one integer n-length 
of the sequence (0 ＜ n ≤ 10 000). The second line contains n integers 
numbers-a1, a2, …, an (-1 000 000 000 000 000 ≤ ai ≤ 1 000 000 000 000 000).
输出：
For each case, on the first line of the output file print the sequence in 
the reverse order.
样例输入：
5
-3 4 6 -8 9
样例输出：
9 -8 6 4 -3
**************************************************************************/
/*
#include <stdio.h>

struct Number{
    char s[18];
}data[10001];

int main(){
    int n;
    int i;
    while(scanf("%d", &n) != EOF){
        for(i=0; i<n; i++)
            scanf("%s", data[i].s);
        for(i=n-1; i>0; i--)
            printf("%s ", data[i].s);
        printf("%s\n", data[i].s);
    }
    return 0;
}
*/

#include <stdio.h>

long long s[10001];

int main(){
    int n;
    int i;
    while(scanf("%d", &n) != EOF){
        for(i=0; i<n; i++)
            scanf("%lld", &s[i]);
        for(i=n-1; i>0; i--)
            printf("%lld ", s[i]);
        printf("%lld\n", s[i]);
    }
    return 0;
}

//给出的数据范围在long long int的范围之类，所以采用字符串读入或是超长整型数的读入两种方案均可以