/*********************************1162************************************
题目描述：
    The country is facing a terrible civil war----cities in the country 
    are divided into two parts supporting different leaders. As a merchant, 
    Mr. M does not pay attention to politics but he actually knows the 
    severe situation, and your task is to help him reach home as soon as possible. 
    "For the sake of safety,", said Mr.M, "your route should contain at 
    most 1 road which connects two cities of different camp."
    Would you please tell Mr. M at least how long will it take to reach 
    his sweet home?
输入：
    The input contains multiple test cases.
    The first line of each case is an integer N (2<=N<=600), representing
     the number of cities in the country.
    The second line contains one integer M (0<=M<=10000), which is the 
    number of roads.
    The following M lines are the information of the roads. Each line
    contains three integers A, B and T, which means the road between 
    city A and city B will cost time T. T is in the range of [1,500].
    Next part contains N integers, which are either 1 or 2. The i-th 
    integer shows the supporting leader of city i. 
    To simplify the problem, we assume that Mr. M starts from city 1 and 
    his target is city 2. City 1 always supports leader 1 while city 2 
    is at the same side of leader 2. 
    Note that all roads are bidirectional and there is at most 1 road 
    between two cities.
Input is ended with a case of N=0.
输出：
    For each test case, output one integer representing the minimum 
    time to reach home.
    If it is impossible to reach home according to Mr. M's demands, 
    output -1 instead.
样例输入：
2
1
1 2 100
1 2
3
3
1 2 100
1 3 40
2 3 50
1 2 1
5
5
3 1 200
5 3 150
2 5 160
4 3 170
4 2 170
1 2 2 2 1
0
样例输出：
100
90
540
**************************************************************************/

#include <stdio.h>
#include <vector>

using namespace std;

struct Road{
    int next;
    int c;
};

struct Dis{
    int dist;
    int flag;
};

int mark[601];
//int dis[601];
int camp[601];

vector<Road> edge[601];
Dis dis[601];

int main(){
    int n, m, a, b, t;
    int i, j, newp, pnext, pc, min;
    while(scanf("%d", &n) != EOF && n != 0){
        scanf("%d", &m);
        for(i=1; i<=n; i++){
            edge[i].clear();
            mark[i] = 0;
            dis[i].dist = -1;
            dis[i].flag = 0;
        }

        while(m-- != 0){
            scanf("%d %d %d", &a, &b, &t);
            Road tmp;
            tmp.c = t;
            tmp.next = b;
            edge[a].push_back(tmp);
            tmp.next = a;
            edge[b].push_back(tmp);
        }

        for(i=1; i<=n; i++){
            scanf("%d", camp+i);
        }

        dis[1].dist = 0;
        mark[1] = 1;
        newp = 1;
        for(i=1; i<n; i++){
            for(j=0; j<edge[newp].size(); j++){
                pnext = edge[newp][j].next;
                pc = edge[newp][j].c;
                if(mark[pnext] == 1)
                    continue;
                if(camp[newp]==camp[pnext] || camp[newp]!=camp[pnext]&&dis[newp].flag==0){
                    if(dis[pnext].dist==-1 || dis[pnext].dist>dis[newp].dist+pc){
                        dis[pnext].dist = dis[newp].dist + pc;
                        if(camp[newp] != camp[pnext])
                            dis[pnext].flag = 1;
                    }
                }
            }

            min = 501;
            for(j=1; j<=n; j++){
                if(mark[j]==1 || dis[j].dist==-1)
                    continue;
                if(min > dis[j].dist){
                    min = dis[j].dist;
                    newp = j;
                }
            }

            mark[newp] = 1;
        }

        printf("%d\n", dis[2]);
    }
    return 0;
}