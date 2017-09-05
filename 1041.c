/*********************************1041************************************
题目描述：
You are given an unsorted array of integer numbers. Your task is to sort 
this array and kill possible duplicated elements occurring in it.
输入：
For each case, the first line of the input contains an integer number N 
representing the quantity of numbers in this array(1≤N≤1000). Next N lines 
contain N integer numbers(one number per each line) of the original array.
输出：
For each case ,outtput file should contain at most N numbers sorted in 
ascending order. Every number in the output file should occur only once.
样例输入：
6
8 8 7 3 7 7
样例输出：
3 7 8
**************************************************************************/

#include <stdio.h>

int main(){
    int a[1001];
    int n;
    int i, j, tmp;
    while(scanf("%d", &n) != EOF){
        for(i=0; i<n; i++)
            scanf("%d", a+i);
        for(i=0; i<n; i++)
            for(j=0; j<n-1-i; j++)
                if(a[j] > a[j+1]){
                    tmp = a[j];
                    a[j] = a[j+1];
                    a[j+1] = tmp;
                }
        for(i=0; i<n-1; i++)
            if(a[i] != a[i+1])
                printf("%d ", a[i]);
        printf("%d\n", a[i]);
    }
    return 0;
}