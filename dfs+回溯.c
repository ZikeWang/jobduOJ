//全排列
#include <stdio.h>

int a[10];
int out[10];
int flag[10];

void dfs(int cnt, int n){
    int i, j;
    if(cnt == n){
        for(i=0; i<cnt; i++)
            printf("%d%c", out[i], i==cnt-1?'\n':' ');
    }
    else{
        for(i=0; i<n; i++){
            if(flag[i] == 0){
                flag[i] = 1;
                out[cnt] = a[i];
                dfs(cnt+1, n);
                flag[i] = 0;
            }
        }
    }
}

int main(){
    int n;
    int i;
    scanf("%d", &n);
    for(i=0; i<10; i++)
        flag[i] = 0;
    for(i=0; i<n; i++)
        scanf("%d", a+i);
    dfs(0, n);
    return 0;
}

————————————————————————————————————————————————————————————————————————
//n个有重复字符的k元全排列
#include <stdio.h>
#include <string.h>

char s[101];
int flag[101];
char tmp[101];
int count;

struct ANSWER{
    char str[101];
}ans[100];

void dfs(int cnt, int k, int len){
    int i, j, tflag;
    if(cnt == k){
        tflag = 1;
        for(i=0; i<count; i++){
            for(j=0; j<k; j++){
                if(ans[i].str[j] != tmp[j]){
                    break;
                }
            }
            if(j == k){
                tflag = 0;
                break;
            }
        }
        if(tflag == 1){
            for(i=0; i<k; i++){
                ans[count].str[i] = tmp[i];
            }
            count++;
        }
    }
    else{
        for(i=0; i<len; i++){
            if(flag[i] == 0){
                flag[i] = 1;
                tmp[cnt] = s[i];
                dfs(cnt+1, k, len);
                flag[i] = 0;
            }
        }
    }
}

int main(){
    int i, j, k, len;
    scanf("%s %d", s, &k);
    len = strlen(s);
    for(i=0; i<101; i++){
        flag[i] = 0;
    }
    count = 0;
    dfs(0, k, len);
    for(i=0; i<count; i++){
        for(j=0; j<k; j++){
            printf("%c", ans[i].str[j]);
        }
        printf("\n");
    }
    return 0;
}

————————————————————————————————————————————————————————————————————————
//素数环
#include <stdio.h>

int out[1000];
int flag[100];
int isprime[20];

void init(){
    int i, j;
    isprime[0] = 0;
    isprime[1] = 0;
    for(i=2; i<20; i++)
        isprime[i] = 1;
    for(i=2; i<20; i++){
        if(isprime[i] == 0)
            continue;
        for(j=i*i; j<20; j+=i)
            isprime[j] = 0;
    }
}

void dfs(int cnt, int n){
    int i;
    if(cnt == n && isprime[out[0]+out[n-1]] == 1){
        for(i=0; i<cnt; i++)
            printf("%d%c", out[i], i==n-1?'\n':' ');
    }
    else{
        for(i=2; i<=n; i++){
            if(flag[i] == 0 && isprime[out[cnt-1]+i]==1){
                flag[i] = 1;
                out[cnt] = i;
                dfs(cnt+1, n);
                flag[i] = 0;
            }
        }
    }
}

int main(){
    init();
    int n;
    int i;
    scanf("%d", &n);
    for(i=0; i<100; i++)
        flag[i] = 0;
    out[0] = 1;
    dfs(1, n);
}

————————————————————————————————————————————————————————————————————————
//插入加号使和最小
#include <stdio.h>
#include <string.h>

int flag[20];
char s[20];
char ans[40];
int anslen;
int min;

int chtoint(int i, int j){
    int result = 0;
    int c = 1;
    int k;
    for(k=j; k>=i; k--){
        result += c * (s[k]-'0');
        c *= 10; 
    }
    return result;
}

int add(int start, int end){
    int i, cnt, result, index[20];
    result = 0;
    cnt = 0;
    for(i=start; i<=end; i++){
        if(flag[i] == 1){
            index[cnt++] = i;
        }
    }
    result = result + chtoint(0, index[0]-1);
    for(i=0; i<cnt-1; i++){
        result = result + chtoint(index[i], index[i+1]-1);
    }
    result = result + chtoint(index[cnt-1], end);
    return result;
}

void dfs(int start, int end, int cnt, int n){
    int i, j;
    if(cnt == n){
        if(add(start, end) < min){
            min = add(start, end);
            anslen = 0;
            for(i=0; i<=end; i++){
                if(flag[i] == 1){
                    ans[anslen++] = '+';
                    ans[anslen++] = s[i];
                }
                else
                    ans[anslen++] = s[i];
            }
        }
    }
    else{
        for(i=start; i<=end; i++){
            if(flag[i] == 0){
                flag[i] = 1;
                dfs(start, end, cnt+1, n);
                flag[i] = 0;
            }
        }
    }
}

int main(){
    int n;
    int i, len;
    for(i=0; i<20; i++)
        flag[i] = 0;
    scanf("%s %d", s, &n);
    len = strlen(s);
    min = 10000000;
    anslen = 0;
    dfs(1, len-1, 0, n);
    for(i=0; i<anslen; i++){
        printf("%c", ans[i]);
    }
    printf("=%d\n", min);
    return 0;
}

————————————————————————————————————————————————————————————————————————
//找所有子集，注意last的作用是为了让每次只找当面元素后面的元素，避免重复
#include <stdio.h>

int array[100];
int flag[100];
int ans[100];

void dfs(int cnt, int amount, int n, int last){
    int i;
    if(cnt == amount){
        for(i=0; i<cnt; i++){
            printf("%d%c", ans[i], i==cnt-1?'\n':' ');
        }
    }
    else{
        for(i=0; i<n; i++){
            if(flag[i]==0 && i>last){
                flag[i] = 1;
                ans[cnt] = array[i];
                dfs(cnt+1, amount, n, i);
                flag[i] = 0;
            }
        }
    }
}

int main(){
    int n;
    int i;
    for(i=0; i<100; i++){
        flag[i] = 0;
    }
    scanf("%d", &n);
    for(i=0; i<n; i++){
        scanf("%d", array+i);
    }
    for(i=1; i<=n; i++){
        dfs(0, i, n, -1);
    }
    return 0;
}

————————————————————————————————————————————————————————————————————————
//最长子序列
#include <stdio.h>
#include <string.h>

char s[100];
char ans[100];
char tmp[100];
int max;

void dfs(int k, int cnt, int n){
    int i;
    if(k == n){
        if(cnt > max){
            max = cnt;
            for(i=0; i<cnt; i++){
                ans[i] = tmp[i];
            }
        }
    }
    else{
        for(i=k; i<n; i++){
            if(cnt==0 || s[i]>tmp[cnt-1]){
                tmp[cnt] = s[i];
                dfs(i+1, cnt+1, n);
            }
            else
                dfs(i+1, cnt, n);
        }
    }
}

int main(){
    int i, len;
    scanf("%s", s);
    len = strlen(s);
    max = 0;
    dfs(0, 0, len);
    printf("max length = %d\n", max);
    for(i=0; i<max; i++){
        printf("%c", ans[i]);
    }
    printf("\n");
    return 0;
}

//改进版
#include <stdio.h>
#include <string.h>

char s[100];
char ans[100];
char tmp[100];
int max;

void dfs(int k, int cnt, int n){
    int i;
    for(i=k; i<n; i++){
        if(cnt==0 || s[i]>tmp[cnt-1]){
            tmp[cnt] = s[i];
            dfs(i+1, cnt+1, n);
        }
    }
    if(i == n){
        if(cnt > max){
            max = cnt;
            for(i=0; i<cnt; i++){
                ans[i] = tmp[i];
            }
        }
    }
}

int main(){
    int i, len;
    scanf("%s", s);
    len = strlen(s);
    max = 0;
    dfs(0, 0, len);
    printf("max length = %d\n", max);
    for(i=0; i<max; i++){
        printf("%c", ans[i]);
    }
    printf("\n");
    return 0;
}

————————————————————————————————————————————————————————————————————————
//加数分解（加数由小到大）
#include <stdio.h>

int number[100];

void dfs(int n, int reminder, int depth, int last)
{
    int i, j;
    if(reminder == 0){
        if(depth!=1){
            printf("%d=", n);
            for(j=0; j<depth; j++){
                printf("%d%c", number[j], j==depth-1?'\n':'+');
            }
        }
    }
    else{
        for(i=last; i<=reminder; i++){
            number[depth]=i;
            dfs(n, reminder-i, depth+1, i);
        }
    }
}

int main(){
    int n;
    while(scanf("%d", &n) != EOF){
        dfs(n,n,0,1);
    }
    return 0;
}

————————————————————————————————————————————————————————————————————————
//部分和问题，只要找到即停止。注意last的使用和Line 342中sum的undo操作
#include <stdio.h>

int array[100];
int flag[100];
int ans[100];
int len;

int dfs(int sum, int l, int k, int n, int last){
    int i;
    if(sum == k){
        len = l;
        return 1;
    }
    else if(sum > k){
        return 0;
    }
    else{
        for(i=0; i<n; i++){
            if(flag[i] == 0 && i > last){
                flag[i] = 1;
                sum += array[i];
                ans[l] = array[i];
                if(dfs(sum, l+1, k, n, i))
                    return 1;
                else{
                    flag[i] = 0;
                    sum -= array[i];
                }
            }
        }
        return 0;
    }
}

int main(){
    int n, k;
    int i;
    for(i=0; i<100; i++){
        flag[i] = 0;
    }
    len = 0;
    scanf("%d %d", &n, &k);
    for(i=0; i<n; i++){
        scanf("%d", array+i);
    }
    if(dfs(0, 0, k, n, -1)){
        printf("Yes\n");
        for(i=0; i<len; i++){
            printf("%d%c", ans[i], i==len-1?'\n':' ');
        }
    }
    else{
        printf("No\n");
    }
    return 0;
}

//输出所有解
#include <stdio.h>

int array[100];
int flag[100];
int ans[100];
int count;

void dfs(int sum, int l, int k, int n, int last){
    int i;
    if(sum == k){
        if(count == 0){
            printf("YES\n");
        }
        count++;
        for(i=0; i<l; i++){
            printf("%d%c", ans[i], i==l-1?'\n':' ');
        }
    }
    else{
        for(i=0; i<n; i++){
            if(flag[i] == 0 && i > last){
                flag[i] = 1;
                sum += array[i];
                ans[l] = array[i];
                dfs(sum, l+1, k, n, i);
                flag[i] = 0;
                sum -= array[i];
            }
        }
    }
}

int main(){
    int n, k;
    int i;
    for(i=0; i<100; i++){
        flag[i] = 0;
    }
    count = 0;
    scanf("%d %d", &n, &k);
    for(i=0; i<n; i++){
        scanf("%d", array+i);
    }
    dfs(0, 0, k, n, -1);
    if(count == 0)
        printf("NO\n");
    return 0;
}

————————————————————————————————————————————————————————————————————————
//8皇后问题
#include <stdio.h>

int N = 8;
int position[8];
int count = 0;

int valid(int row){
    int i;
    for(i=0; i<row; i++){
        if(position[i]==position[row] || abs(position[i]-position[row])==abs(i-row))
            return 0;
    }
    return 1;
}

void dfs(int row){
    int i, column;
    if(N == row){
        printf("solution %d\n", ++count);
        for(i=0; i<N; i++)
            printf("%d %d\n", i, position[i]);
    }
    else{
        for(column = 0; column < N; ++column){
            position[row] = column;
            if(valid(row) == 1)
                dfs(row+1);// 如果不满足条件，则进行下一次循环，即回溯回去在第row行重新寻找摆放的位置
        }
    }
}

int main(){
    dfs(0);
    return 0;
}

