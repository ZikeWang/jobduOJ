/*********************************1100************************************
题目描述：
N个城市，标号从0到N-1，M条道路，第K条道路（K从0开始）的长度为2^K，求编号
为0的城市到其他城市的最短距离
输入：
第一行两个正整数N（2<=N<=100）M(M<=500),表示有N个城市，M条道路
接下来M行两个整数，表示相连的两个城市的编号
输出：
N-1行，表示0号城市到其他城市的最短路，如果无法到达，输出-1，数值太大的
以MOD 100000 的结果输出。
样例输入：
4 4
1 2
2 3
1 3
0 1
样例输出：
8
9
11
**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

struct Road
{
    int next;
    char c[5000];
};

struct Dis
{
    char len[5000];
    int flag;
}dis[101];

vector<Road> edge[101];
int mark[101];

int cmp(char *s1, char *s2){
    int i, ls1, ls2;
    for(i=0; i<5000; i++){
        if(s1[i] == '\0')
            break;
    }
    ls1 = i+1;
    for(i=0; i<5000; i++){
        if(s2[i] == '\0')
            break;
    }
    ls2 = i+1;

    if(ls1 != ls2)
        return ls1>ls2 ? 1 : 0;
    else{
        for(i=ls1-1; i>=0; i--){
            if(s1[i] == s2[i])
                continue;
            else if(s1[i] > s2[i])
                return 1;
            else
                return 0;
        }
        return 0;
    }
}

int main(){
    int n, m;
    int i, j, k, a, b, newp, pnext, lp, lpc, lnewp, carry, atmp, c;
    char power[5000], snewp[5000], pc[5000], result[5000], min[5000];

    while(scanf("%d %d", &n, &m) != EOF){
        for(i=0; i<n; i++){
            edge[i].clear();
            mark[i] = 0;
            dis[i].flag = 0;
            for(j=0; j<5000; j++){
                power[j] = '\0';
                dis[i].len[j] = '\0';
            }
        }
        
        power[0] = 1 + '0';
        while(m-- != 0){
            scanf("%d %d", &a, &b);
            Road tmp;
            strcpy(tmp.c, power);
            tmp.next = b;
            edge[a].push_back(tmp);
            tmp.next = a;
            edge[b].push_back(tmp);

            lp = strlen(power);
            carry = 0;
            for(i=0; i<lp; i++){
                atmp = power[i]-'0' + power[i]-'0' + carry;
                carry = atmp / 10;
                power[i] = atmp % 10 + '0';
            }
            if(carry)
                power[i] = carry + '0';
        }

        dis[0].len[0] = '0';
        dis[0].flag = 1;
        mark[0] = 1;
        newp = 0;
        for(i=0; i<n; i++){
            for(j=0; j<edge[newp].size(); j++){
                for(k=0; k<5000; k++){
                    snewp[k] = '\0';
                    pc[k] = '\0';
                    result[k] = '\0';
                }
                pnext = edge[newp][j].next;
                strcpy(pc, edge[newp][j].c);

                if(mark[pnext] == 1)
                    continue;
                
                strcpy(snewp, dis[newp].len);
                lnewp = strlen(snewp);
                lpc = strlen(pc);
                if(lnewp > lpc){
                    for(k=lpc; k<lnewp; k++)
                        pc[k] = '0';
                    lpc = lnewp;
                }
                else if(lnewp < lpc){
                    for(k=lnewp; k<lpc; k++)
                        snewp[k] = '0';
                    lnewp = lpc;
                }
                carry = 0;
                for(k=0; k<lpc; k++){
                    atmp = snewp[k]-'0' + pc[k]-'0' + carry;
                    carry = atmp / 10;
                    result[k] = atmp % 10 + '0';
                }
                if(carry)
                    result[k] = carry + '0';

                if(dis[pnext].flag == 0 || cmp(dis[pnext].len, result) == 1){
                    dis[pnext].flag = 1;
                    strcpy(dis[pnext].len, result);
                }
            }

            for(k=0; k<5000; k++)
                min[k] = '9';
            for(j=0; j<n; j++){
                if(mark[j] == 1 || dis[j].flag == 0)
                    continue;
                if(cmp(dis[j].len, min) == 0){
                    strcpy(min, dis[j].len);
                    newp = j;
                }
            }
            mark[newp] = 1;
        }

        for(i=1; i<n; i++){
            if(dis[i].flag==1){
                atmp = 0;
                c = 1;
                for(j=0; j<7; j++){
                    if(dis[i].len[j]>'9' || dis[i].len[j]<'0')
                        break;
                    atmp =atmp + (dis[i].len[j]-'0')*c;
                    c *= 10;
                }
                atmp %= 100000;
                printf("%d\n", atmp);
            }
            else
                printf("-1\n");
        }
        
    }
    return 0;
}

/*#include <stdio.h>
#include <vector>
 
using namespace std;
 
struct Road
{
    int next;
    int c;
};
 
vector<Road> edge[101];
int mark[101];
int dis[101];
 
int main(){
    int n, m;
    int i, j, power, a, b, newp, pnext, pc, min;
    while(scanf("%d %d", &n, &m) != EOF){
        power = 1;
        for(i=0; i<n; i++)
            edge[i].clear();
        for(i=0; i<n; i++){
            mark[i] = 0;
            dis[i] = -1;
        }
 
        while(m-- != 0){
            scanf("%d %d", &a, &b);
            Road tmp;
            tmp.c = power;
            tmp.next = b;
            edge[a].push_back(tmp);
            tmp.next = a;
            edge[b].push_back(tmp);
            power *= 2;
            power %= 100000;
        }
 
        dis[0] = 0;
        mark[0] = 1;
        newp = 0;
        for(i=0; i<n; i++){
            for(j=0; j<edge[newp].size(); j++){
                pnext = edge[newp][j].next;
                pc = edge[newp][j].c;
                if(mark[pnext] == 1)
                    continue;
                if(dis[pnext] == -1 || dis[pnext] % 100000> (dis[newp]%100000 + pc%100000)%100000)
                    dis[pnext] = (dis[newp]%100000 + pc%100000)%100000;
            }
 
            min = 100000;
            for(j=0; j<n; j++){
                if(mark[j] == 1 || dis[j] == -1)
                    continue;
                if(dis[j] < min){
                    min = dis[j];
                    newp = j;
                }
            }
 
            mark[newp] = 1;
        }
 
        for(i=1; i<n; i++)
            printf("%d\n", dis[i]%100000);
         
    }
    return 0;
}*/

/***********************************************************
这道题首先要考虑到是大数问题，因此涉及到高精度计算的应该选用
字符串操作来进行。题目的思路不算复杂，使用邻接链表实现迪杰斯
特拉算法。主要问题出在对高精度数的计算以及比较不太熟练。另外
数组定义过小会导致WA，之前错误就在于大小定义成了1000
************************************************************/