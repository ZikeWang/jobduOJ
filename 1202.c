/*********************************1202************************************
题目描述：
    对输入的n个数进行排序并输出。
输入：
    输入的第一行包括一个整数n(1<=n<=100)。
    接下来的一行包括n个整数。
输出：
    可能有多组测试数据，对于每组数据，将排序后的n个整数输出，每个数后面都有一个空格。
    每组测试数据的结果占一行。
样例输入：
4
1 4 3 2
样例输出：
1 2 3 4 
**************************************************************************/

#include <stdio.h>
 
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
 
int main(void){
    int buf[100];
    int i, j;
    int n;
    while( scanf("%d", &n) != EOF ){
        for(i = 0; i < n; i++)
            scanf("%d", buf+i);
        for(i = 0; i < n; i++)
            for(j = i; j < n; j++){
                if( buf[i] >= buf[j] )
                    swap( buf+i, buf+j);
            }
        for(i = 0; i < n; i++)
            printf("%d ", buf[i]);
        printf("\n");
    }
    return 0;
}