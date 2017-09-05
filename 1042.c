/*********************************1042************************************
题目描述：
Find a longest common subsequence of two strings.
输入：
First and second line of each input case contain two strings of lowercase 
character a…z. There are no spaces before, inside or after the strings. 
Lengths of strings do not exceed 100.
输出：
For each case, output k – the length of a longest common subsequence in one line.
样例输入：
abcd
cxbydz
样例输出：
2
**************************************************************************/

#include <stdio.h>
#include <string.h>

#define max(x,y) x>y?x:y

int main(){
    char s1[101], s2[101];
    int d[101][101];
    int i, j, l1, l2;
    while(scanf("%s %s", s1, s2) != EOF){
        l1 = strlen(s1);
        l2 = strlen(s2);
        for(i=0; i<l1+1; i++)
            d[i][0] = 0;
        for(i=0; i<l2+1; i++)
            d[0][i] = 0;
        for(i=0; i<l1; i++)
            for(j=0; j<l2; j++){
                if(s1[i] == s2[j])
                    d[i+1][j+1] = d[i+1-1][j+1-1] + 1;
                else
                    d[i+1][j+1] = max(d[i+1][j+1-1], d[i+1-1][j+1]);
            }
        printf("%d\n", d[l1][l2]);
    }
    return 0;
}

//重点掌握LCS的状态转移方程