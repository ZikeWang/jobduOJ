/*********************************1450************************************
题目描述：
有一群人，打乒乓球比赛，两两捉对撕杀，每两个人之间最多打一场比赛。
球赛的规则如下：
如果A打败了B，B又打败了C，而A与C之间没有进行过比赛，那么就认定，A一定能打败C。
如果A打败了B，B又打败了C，而且，C又打败了A，那么A、B、C三者都不可能成为冠军。
根据这个规则，无需循环较量，或许就能确定冠军。你的任务就是面对一群比赛选手，
在经过了若干场撕杀之后，确定是否已经实际上产生了冠军。
输入：
输入含有一些选手群，每群选手都以一个整数n(n<1000)开头，后跟n对选手的比赛结果，
比赛结果以一对选手名字（中间隔一空格）表示，前者战胜后者。如果n为0，则表示输入结束。
输出：
对于每个选手群，若你判断出产生了冠军，则在一行中输出“Yes”，否则在一行中输出“No”。
样例输入：
3
Alice Bob
Smith John
Alice Smith
5
a c
c d
d e
b e
a d
0
样例输出：
Yes
No
**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

vector<int> edge[1001];
queue<int> Q;

struct Name{
    char s[100];
}name[1001];

int inDegree[1001];

int main(){
    int n;
    int i, j, a, b, cnt, initcnt, outcnt, x;
    char str1[100], str2[100];
    while(scanf("%d", &n) != EOF && n != 0){
        cnt = 0;
        for(i=0; i<1001; i++){
            edge[i].clear();
            inDegree[i] = 0;
            for(j=0; j<100; j++)
                name[i].s[j] = '\0';
        }

        while(Q.empty() == 0)
            Q.pop();

        for(i=0; i<n; i++){
            scanf("%s %s", str1, str2);
            for(j=0; j<1001; j++)
                if(strcmp(str1, name[j].s) == 0){
                    a = j;
                    break;
                }
            if(j == 1001){
                strcpy(name[cnt++].s, str1);
                a = cnt-1;
            }
            for(j=0; j<1001; j++)
                if(strcmp(str2, name[j].s) == 0){
                    b = j;
                    break;
                }
            if(j == 1001){
                strcpy(name[cnt++].s, str2);
                b = cnt-1;
            }
            edge[a].push_back(b);
            inDegree[b]++;
        }
        
        initcnt = 0;

        for(i=0; i<cnt; i++)
            if(inDegree[i] == 0){
                Q.push(i);
                initcnt++;
            }

        outcnt = 0;
        while(Q.empty() == 0){
            x = Q.front();
            Q.pop();
            outcnt++;
            for(i=0; i<edge[x].size(); i++){
                inDegree[edge[x][i]]--;
                if(inDegree[edge[x][i]] == 0)
                    Q.push(edge[x][i]);
            }
        }

        if(outcnt == cnt && initcnt == 1)
            printf("Yes\n");
        else
            printf("No\n");

    }
    return 0;
}

/**************************************************************
这道题有四个地方需要注意：
1.提交出现WA的原因在于存放name的字符串定义小了，一开始定义成的
10个char大小太小了，改成了100大小的就可以了。
2.要注意各种数据类型的运用，例如本题在结构体E中定义name的话，后
面的vector的使用会带来不变，那么可以用一个数组来单独存放name，
只要下标一致即可，但这时使用二维数组也比较麻烦，那么进而选择使用
结构体数组来取代，同样保证下标一致即可。
3.本题中算法的一个关键之处在于：要使得能产生正确的排序（即冠军），
初始时入度为0的结点只能有一个，这个可以通过画图看出来，之前在设计
算法的时候没有考虑到。
4.输入问题，经验证明使用getchar(),get()等后进行字符操作处理输入流
极易引发runtime error，应该尽量使用scanf()处理，这道题每次输入2
个字符串中间有空格的，直接两个%s即可。
***************************************************************/