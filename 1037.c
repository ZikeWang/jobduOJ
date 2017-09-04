/*********************************1037************************************
题目描述：
    Today, facing the rapid development of business, SJTU recognizes that 
    more powerful calculator should be studied, developed and appeared in 
    future market shortly. SJTU now invites you attending such amazing 
    research and development work.
    In most business applications, the top three useful calculation operators 
    are Addition (+), Subtraction (-) and Multiplication (×) between two 
    given integers. Normally, you may think it is just a piece of cake. 
    However, since some integers for calculation in business application 
    may be very big, such as the GDP of the whole world, the calculator 
    becomes harder to develop.
    For example, if we have two integers 20 000 000 000 000 000 and 
    4 000 000 000 000 000, the exact results of addition, subtraction 
    and multiplication are:
    20000000000000000 + 4000000000000000 = 24 000 000 000 000 000
    20000000000000000 - 4000000000000000 = 16 000 000 000 000 000
    20000000000000000 × 4000000000000000 = 80 000 000 000 000 000 000 000 000 000 000
    Note: SJTU prefers the exact format of the results rather than the float 
    format or scientific remark format. For instance, we need "24000000000000000" 
    rather than 2.4×10^16.
    As a programmer in SJTU, your current task is to develop a program to obtain 
    the exact results of the addition (a + b), subtraction (a - b) and 
    multiplication (a × b) between two given integers a and b.
输入：
   Each case consists of two separate lines where the first line gives the integer 
   a and the second gives b (|a| <10^400 and |b| < 10^400).
输出：
    For each case, output three separate lines showing the exact results of 
    addition (a + b), subtraction (a - b) and multiplication (a × b) of that case, 
    one result per lines.
样例输入：
20000000000000000
4000000000000000
样例输出：
24000000000000000
16000000000000000
80000000000000000000000000000000
**************************************************************************/

#include <stdio.h>
#include <string.h>

char a[500];
char b[500];
int a1[500];
int b1[500];
int mul[1000];
int add[1000];
int sub[1000];

int substract(int *x, int *y, int l){
    int i, tx[500], ty[500];
    for(i=0; i<500; i++){
        tx[i] = x[i];
        ty[i] = y[i];
    }
    for(i=0; i<l; i++){
        if(tx[i] >= ty[i])
            sub[i] = tx[i] - ty[i];
        else{
            tx[i+1]--;
            sub[i] = tx[i] + 10 - ty[i];
        }
    }
    for(i=l-1; i>0; i--){
        if(sub[i] == 0)
            l--;
        else
            break;
    }
    return l;
}

int main(){
    int pa, pb, i, j, len1, len2, mlen, slen, alen, carry, tmp, flag;
    while(scanf("%s %s", a, b) != EOF){
        for(i=0; i<1000; i++){
            mul[i] = 0;
        }

        len1 = strlen(a);
        len2 = strlen(b);

        if(a[0] == '-'){
            pa = -1;
            for(i=0; i<len1; i++)
                a[i] = a[i+1];
            len1--;
        }
        else
            pa = 1;

        if(b[0] == '-'){
            pb = -1;
            for(i=0; i<len2; i++)
                b[i] = b[i+1];
            len2--;
        }
        else
            pb = 1;

        mlen = len1 + len2;
        for(i=0; i<len1; i++)
            a1[i] = a[len1-1-i] - '0';
        for(i=0; i<len2; i++)
            b1[i] = b[len2-1-i] - '0';
        for(i=0; i<len1; i++)
            for(j=0; j<len2; j++){
                mul[i+j] += a1[i] * b1[j];
                mul[i+j+1] += mul[i+j] / 10;
                mul[i+j] = mul[i+j] % 10;
            }
        if(mul[mlen-1] == 0)
            mlen--;

        if(len1 > len2){
            for(i=len2; i<len1; i++)
                b1[i] = 0;
            alen = len1;
            slen = substract(a1, b1, len1);
            flag = 1;
        }
        else if(len1 < len2){
            for(i=len1; i<len2; i++)
                a1[i] = 0;
            alen = len2;
            slen = substract(b1, a1, len2);
            flag = 0;
        }
        else{
            alen = len1;
            for(i=len1-1; i>=0; i--){
                if(a1[i] == b1[i])
                    continue;
                else if(a1[i] > b1[i]){
                    slen = substract(a1, b1, len1);
                    flag = 1;
                    break;
                }
                else{
                    slen = substract(b1, a1, len2);
                    flag = 0;
                    break;
                }
            }
            if(i<0){
                flag = 2;
                slen = 1;
                sub[0] = 0;
            }
        }

        carry = 0;
        for(i=0; i<alen; i++){
            tmp = a1[i] + b1[i] + carry;
            carry = tmp / 10;
            add[i] = tmp % 10;
        }
        if(carry){
            add[i] = carry;
            alen++;
        }

        if(pa==1 && pb==1){
            for(i=alen-1; i>=0; i--)
                printf("%d", add[i]);
            printf("\n");
            if(flag==1){
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            else if(flag==0){
                printf("-");
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            else{
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            for(i=mlen-1; i>=0; i--)
                printf("%d", mul[i]);
            printf("\n");
        }
        else if(pa==1 && pb==-1){
            if(flag==1){
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            else if(flag==0){
                printf("-");
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            else{
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            for(i=alen-1; i>=0; i--)
                printf("%d", add[i]);
            printf("\n");
            printf("-");
            for(i=mlen-1; i>=0; i--)
                printf("%d", mul[i]);
            printf("\n");
        }
        else if(pa==-1 && pb==1){
            if(flag==1){
                printf("-");
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            else if(flag==0){
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            else{
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            printf("-");
            for(i=alen-1; i>=0; i--)
                printf("%d", add[i]);
            printf("\n");
            printf("-");
            for(i=mlen-1; i>=0; i--)
                printf("%d", mul[i]);
            printf("\n");
        }
        else if(pa==-1 && pb==-1){
            printf("-");
            for(i=alen-1; i>=0; i--)
                printf("%d", add[i]);
            printf("\n");
            if(flag==1){
                printf("-");
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            else if(flag==0){
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            else{
                for(i=slen-1; i>=0; i--)
                    printf("%d", sub[i]);
                printf("\n");
            }
            for(i=mlen-1; i>=0; i--)
                printf("%d", mul[i]);
            printf("\n");
        }
    }
    return 0;
}

/****************************************************************
本题暴露出了较多的问题，主要原因在与思维的不严谨导致设计算法时漏
解，另外在一些细节的处理上也出现了问题。
1.高精度乘法的核心算法要掌握，主要是Line 103-115
2.在运用高精度乘法的算法时，最后一步去零操作很重要，即Line 114和
Line 155，两个长度分别为l1和l2的大数相乘，根据乘法运算原理，所得
结果的长度最大为l1+(l2-1)+1=l1+l2，如果不产生进位的话则为l1+l2-1，
所以我们应该判读最高位是否为0从而确定运算结果的实际长度，但是前面
提交时出错就是在于直接访问了数组的mul[mlen]，这样忽视了数组从0计
数的特点，即结果的第mlen即l1+l2个数位应该对应的数组下标为mlen-1
3.在运用高精度减法的操作时，极有可能产生借位操作，如果直接在原始
数据上进行借位操作的话，修改了原始数据，那么如果后面还要使用到原
始数据的话例如还要进行加法运算，就会出错。Line 53新增临时数组tx，
ty就是避免这样的错误。
4.漏解，变量悬空。在最后打印时要根据flag的值进行分支，但flag没有
赋初值，另外Line 131-152在修改前并没有考虑如果两数相等时的处理方
案，两个问题叠加在一起就出现错误了。因此需要增加对相等情况的处理
以及该情况下flag的处理以便在最后根据flag进行分支打印。
5.在Line 66-71的去零操作中，应考虑到如果计算的结果为零，那么不能
将最后一个零去掉，即要考虑到边界问题，类似于问题2。
6.要考虑到四则运算的正负问题，一开始只考虑到了两个操作数都是正数
的情况，这样显然是很不周全的。
*****************************************************************/