/*********************************1038************************************
题目描述：
    John von Neumann, b. Dec. 28, 1903, d. Feb. 8, 1957, was a Hungarian-American 
    mathematician who made important contributions to the foundations of mathematics, 
    logic, quantum physics, meteorology, science, computers, and game theory. 
    He was noted for a phenomenal memory and the speed with which he absorbed 
    ideas and solved problems. In 1925 he received a B.S. diploma in chemical 
    engineering from Zurich Institute and in 1926 a Ph.D. in mathematics from 
    the University of Budapest, His Ph.D. dissertation on set theory was an 
    important contributions to the subject.
    At the age of 20, von Neumann proposed a new definition of ordinal numbers 
    that was universally adopted. While still in his twenties, he made many 
    contributions in both pure and applied mathematics that established him as 
    a mathematician of unusual depth. His Mathematical Foundation of Quantum 
    Mechanics (1932) built a solid framework for the new scientific discipline.
    During this time he also proved the mini-max theorem of GAME THEORY. He 
    gradually expanded his work in game theory, and with coauthor Oskar Morgenstern 
    he wrote Theory of Games and Economic Behavior (1944).
    There are some numbers which can be expressed by the sum of factorials. 
    For example 9, 9 = 1! + 2! + 3! . Dr. von Neumann was very interested in 
    such numbers. So, he gives you a number n, and wants you to tell whether 
    or not the number can be expressed by the sum of some factorials.
    Well, it is just a piece of case. For a given n, you will check if there are 
    some xi, and let n equal to Σt (上标) i=1（下标） xi! (t≥1, xi≥0, xi = xj <==> i = j)
        t
     即 Σ  xi! (t≥1, xi≥0, xi = xj <==> i = j)
       i=1
    If the answer is yes, say "YES"; otherwise, print out "NO".
输入：
    You will get a non-negative integer n (n≤1,000,000) from input file.
输出：
    For the n in the input file, you should print exactly one word ("YES" or "NO") 
    in a single line. No extra spaces are allowed.
样例输入：
9
2
样例输出：
YES
YES
**************************************************************************/
/*error
#include <stdio.h>

int fac[11];

int factorial(int x){
    if(x == 1)
        return 1;
    else
        return x*factorial(x-1);
}

void init(){
    int i;
    fac[0] = 1;
    for(i=1; i<=10; i++)
        fac[i] = factorial(i);
}

int add(int i, int j){
    int s = 0;
    int t;
    for(t=i; t<=j; t++)
        s += fac[t];
    return s;
}


int main(){
    int n;
    int i, j, ans;
    init();
    while(scanf("%d", &n) != EOF){
        ans = 0;
        for(i=0; i<=10; i++){
            for(j=i; j<=10; j++){
                if(add(i, j) == n){
                    ans = 1;
                    break;
                }
            }
            if(ans == 1)
                break;
        }

        if(ans)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
*/

#include <stdio.h>

int fac[10];
int n;
int sum;
int flag[10];

int factorial(int x){
    if(x == 1)
        return 1;
    else
        return x*factorial(x-1);
}

void init(){
    int i;
    fac[0] = 1;
    for(i=1; i<10; i++)
        fac[i] = factorial(i);
}


int dfs(int x){
    sum += fac[x];
    flag[x] = 1;
    int i;
    if(sum == n)
        return 1;
    else if(sum < n){
        for(i=x-1; i>=0; i--){
            int state = dfs(i);
            if(state == 1)
                return 1;
            else{
                flag[i] = 0;
                sum -= fac[i];
            }
        }
    }
    return 0;
}

int main(){
    int i, j, top, ans;
    init();
    while(scanf("%d", &n) != EOF){
        for(i=0; i<10; i++)
            flag[i] = 0;
        top = 0;
        for(i=0; i<9; i++){
            if(fac[i]<=n && fac[i+1]>n){
                top = i;
                break;
            }
        }
        if(i==9)
            top = 9;
        sum = 0;
        if(dfs(top) == 1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

/*************************************************************************
1.这道题浪费了太多的不必要时间，究其原因就是在一个错误的算法上死磕，在代码
过程中发现不了错误而发现不了根本问题，白白浪费时间。根本原因在于没有审清题
目的要求和意思，从而被自己的错误理解而误导，越走越歪。在审清题意后还要对算
法等做出好的选择，有了大体的思路后再开始代码，盲目开始代码的习惯不好。对于
这道题而言，题目中关键的一句是：For a given n, you will check if there are 
some xi, and let n equal to Σt (上标) i=1（下标） xi! 
(t≥1, xi≥0, xi = xj <==> i = j)
   t
即 Σ  xi! (t≥1, xi≥0, xi = xj <==> i = j)
  i=1
题目的意思是说，符合要求的加数（阶乘的值）中，每个加数（a！）的阶乘底数（a）
保存在xi中，也就是说从x1到xi最后到xt每个x都保存一个底数，这些被选择的数相
当于放在了一个顺序的数组里排列了。而不是说要选择从1的阶乘到另一个数的阶乘中
某个连续的序列，让他们的和等于一个输入的数，这样就缩小了解的空间。前面提交
了很多次的代码中没有注意到这个问题，所以都是以连续序列为前提要求在求解，所
以无论怎么提交都是错误的

2.要注意数值的范围。之前在自己测的时候，输入例如100来求其阶乘结果显示是0，
遇到这样的问题一方面要考虑是否是算法或代码哪里出了问题，另一方面对于这种
阶乘、大数运算等类似的问题，下意识的要反应是否数据类型不够产生溢出等原因。
对于本题而言，应先做个估算，10的阶乘比题目要求的要大，因此计算到10的阶乘
即可，另外，要求的数据在int范围内，因此用int保存数据即可，大可不必使用long

3.注意循环边界（递归出口）问题。这类问题有时不会产生影响，但有时极为致命，
因此在使用诸如循环、递归等操作要定界时，一定要仔细斟酌。例如本题中，Line
103对递归出口的设定；Line 112由于10的阶乘是大于n的最大值的，所以在计算中肯
定用不上，所以只需计算0-9的阶乘；Line 144由于后面的判断要去数组i+1的值，所
以循环要求到数组的倒数第二个值就应该停止了

4.要使用的值一定要考虑到他的各种情况，不要让值悬空。这一点主要体现在Line 143
和Line 150-151。在确定top值时，只有当满足if条件时top才被赋值，而当n为0或者是
位于9！和n最大可能取值之间时，是不满足if条件语句的，所以这里还需单独赋值

5.特殊情况的考虑，即0的阶乘为1。

6.算法的选择，本题是采用dfs+递归+回溯，后面的贪心算法和更简单的dfs值得学习
另外对各阶乘值的计算，Line 209-212和Line 240-242也是值得借鉴的方法

7.使用贪心的原因和阶乘的性质有关，因为f[i] > sum(f[0],,,,f[i-1])。 如果n是
sum of factorials，且n>=f[i], 那么n中一定包含f[i],否则后面的所有f[0]...f[i-1]
的和加起来都小于n
**************************************************************************/

/*贪心
#include <stdio.h>  
  
int main()  
{  
    int i, j, n;  
    while(scanf("%d",&n) != EOF)  
    {  
        int buf[10];  
        buf[0] = 1;  
        for(i = 1; i < 10; i++)  
            buf[i] = i * buf[i-1];  
  
        for(j = 9; j >= 0; j--)  
        {  
            if(n >= buf[j])  
                n -= buf[j];  
        }  
        if(n == 0)  
            printf("YES\n");  
        else  
            printf("NO\n");  
    }  
  
    return 0;  
}  
*/

/*dfs
#include <stdio.h>  
  
static int f[11];  
static int n;  
  
void make_f(){   
    f[0] = 1;  
    for (int i = 1; i < 11 ; ++i) {   
        f[i] = i * f[i-1];   
    }    
}    
  
bool dfs(int x, int l){   
    if(x==n)
        return true;    
    if(l>10)
        return false;   
    if(x>n)
        return false;   
    bool b0 = dfs(x,l+1);   
    if(b0)
        return true;   
    x += f[l];  
    bool b1 = dfs(x,l+1);   
    return b1;  
}   
  
int main(){   
    make_f();   
    while(scanf("%d",&n) !=EOF){   
        if(n==0)
            printf("NO\n");     
        else
            printf("%s\n",dfs(0,0)?"YES":"NO");   
    }    
}    
*/