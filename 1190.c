/*********************************1190************************************
题目描述：
对N个长度最长可达到1000的数进行排序。
输入：
输入第一行为一个整数N，(1<=N<=100)。
接下来的N行每行有一个数，数的长度范围为1<=len<=1000。
每个数都是一个正数，并且保证不包含前缀零。
输出：
可能有多组测试数据，对于每组数据，将给出的N个数从小到大进行排序，输出排序
后的结果，每个数占一行。
样例输入：
3
11111111111111111111111111111
2222222222222222222222222222222222
33333333
样例输出：
33333333
11111111111111111111111111111
2222222222222222222222222222222222
**************************************************************************/
#include <stdio.h>
#include <string.h>

typedef struct biginteger{
	char str[1001];
	int len;
}biginteger;

biginteger num[101];

int main(){
	int N;
	int i, j;
	char tmp_digit[1001];
	char tmp_length;
	while(scanf("%d", &N) != EOF){
		for(i=0; i<N; i++){
			memset(num[i].str, 0, sizeof(num[i].str));
			scanf("%s", num[i].str);
			num[i].length = strlen(num[i].str);
		}
		for(i=0; i<N; i++)
			for(j=0; j<N-1-i; j++){
				if( num[j].length>num[j+1].length){
					tmp_length = num[j].length;
					num[j].length = num[j+1].length;
					num[j+1].length = tmp_length;
					strcpy(tmp_digit, num[j].str);
					strcpy(num[j].str, num[j+1].str);
					strcpy(num[j+1].str, tmp_digit);
				}
				else if(num[j].length==num[j+1].length&&strcmp(num[j].str, num[j+1].str)>0){
					tmp_length = num[j].length;
					num[j].length = num[j+1].length;
					num[j+1].length = tmp_length;
					strcpy(tmp_digit, num[j].str);
					strcpy(num[j].str, num[j+1].str);
					strcpy(num[j+1].str, tmp_digit);
				}
			}
		for(i=0; i<N; i++)
			printf("%s\n", num[i].str);
	}
	return 0;
}

/*
#include <stdio.h>
#include <string.h>
 
struct biginteger{
    char digit[1002];
    int length;
}num[102];
 
int sub(int i, int j){
    int k;
    if(num[i].length != num[j].length)
        return num[i].length>num[j].length ? 1 : 0;
    else{
        for(k=0; k<num[i].length; k++){
            if(num[i].digit[k] == num[j].digit[k])
                continue;
            else if(num[i].digit[k] > num[j].digit[k])
                return 1;
            else
                return 0;
        }
        return 0;
    }
}
 
void swap(int i, int j){
    char tmp_digit[1002];
    int tmp_length;
    strcpy(tmp_digit, num[i].digit);
    tmp_length = num[i].length;
    strcpy(num[i].digit, num[j].digit);
    num[i].length = num[j].length;
    strcpy(num[j].digit, tmp_digit);
    num[j].length = tmp_length;
}
 
int main(){
    int N;
    int i, j, l;
    while(scanf("%d", &N) != EOF){
        for(i=0; i<N; i++){
            scanf("%s", num[i].digit);
            num[i].length = strlen(num[i].digit);
        }
        for(i=0; i<N; i++)
            for(j=0; j<N-1-i; j++)
                if( sub(j, j+1)>0 ){
                    swap(j, j+1);
                }
        for(i=0; i<N; i++)
            printf("%s\n", num[i].digit);
    }
    return 0;
}
*/

/*
#include <stdio.h>
#include <string.h>
  
struct biginteger{
    char digit[1001];
    int length;
}num[101];
  
int sub(int i, int j){
    int k, len, tmp;
    char tmpi[1001], tmpj[1001];
    strcpy(tmpi, num[i].digit);
    strcpy(tmpj, num[j].digit);
    tmpi[num[i].length] = '\0';
    tmpj[num[j].length] = '\0';
    if(num[i].length != num[j].length)
        return num[i].length>num[j].length ? 1 : 0;
    else{
        //result = 0;
        //c = 1;
        len = num[i].length;
        for(k=len-1; k>0; k--){
            tmp = tmpi[k]-tmpj[k];
            if( tmp < 0 ){
                tmpi[k-1] -= 1;
                //result = result + (tmp + 10)*c;
            }
            //else{
                //result = result + tmp * c;
            //}
            //c *= 10;
        }
        tmp = tmpi[k]-tmpj[k];
        if(tmp < 0)
            return 0;
        //else if(tmp == 0){
            //if(result > 0)
                //return 1;
            //else
                //return 0;
        //}
        else
            return 1; 
    }
}
  
void swap(int i, int j){
    char tmp_digit[1001];
    int tmp_length;
    strcpy(tmp_digit, num[i].digit);
    tmp_length = num[i].length;
    tmp_digit[tmp_length] = '\0';
    strcpy(num[i].digit, num[j].digit);
    num[i].length = num[j].length;
    num[i].digit[num[i].length] = '\0';
    strcpy(num[j].digit, tmp_digit);
    num[j].length = tmp_length;
    num[j].digit[num[j].length] = '\0';
}
  
int main(){
    int N;
    int i, j, l;
    while(scanf("%d", &N) != EOF){
        for(i=0; i<N; i++){
            scanf("%s", num[i].digit);
            num[i].length = strlen(num[i].digit);
        }
        for(i=0; i<N; i++)
            for(j=0; j<N-1-i; j++)
                if( sub(j, j+1)>0 ){
                    swap(j, j+1);
                }
        for(i=0; i<N; i++)
            printf("%s\n", num[i].digit);
    }
    return 0;
}
*/

/********************************************************************
这道题的解题过程中暴露出来的细节问题较严重
关于这道题有以下几点值得注意：
1.方案的选择问题：如果题目可能涉及到二维数组问题，而对于二维数组的
操作比较困难时，选择用结构体数组来代替较为理想，另外结构体数组内还
能保存数组长度等数据，因此很多时候相较于二维数组而言可能更方便
2.数据类型的定义：这道题解题过程中出现了两个这方面的错误
（1）在交换两个结构体时，对于存放交换过程中临时数据length定义了一个
tmp_length变量，但是本应该定义成int类型的，却错误的定义成了char类型，
这样的话当字符串过长时（特别是在处理大数据、高精度问题时）很容易发生
溢出从而导致错误，除此之外类型不一致也极易导致错误
（2）在使用高精度（大数据）减法的函数中，使用int类型的result来保存
减法的结果，然后对result的值进行判断确定函数的返回值。乍一看没有问题，
当数据的精度在int范围内确实没毛病，但注意result应用的场景是大数减法，
因此result的结果极有可能发生溢出错误。因此一定要更根据应用的场景采取
合适的数据定义，或者选择合适的方法去避免正面处理问题。例如ac的解法中
就根据减法的特点避开了使用result结果去判断。
3.保证变量、参数的一致性。例如for循环中使用某一计数变量时，三个条件中
都应保持一致，切忌因为手误或者修改变量时没有修改全而导致的不一致；又
如前面大的循环里使用了一个计数变量，那么在循环体内就要避免使用该变量
甚至是修改该变量
4.对于取数组或其他变量的值参与计算时，如果这些值理应不被修改或者在后
面的程序中暂时还要被调用时，那么一定要避免对这些数据的修改，特别是计
算过程中会修改其值的。这时可以选用一个temp变量做一个拷贝，然后对temp
变量进行操作。总的来说就是对一个值的更新或修改，一定要保证在对该值的
所有使用结束后才能进行。本题第三种方案做减法时使用tmpi和tmpj就是防止
该错误的发生。另外在#1161和#1437中都出现过类似问题
5.对于for循环一定要注意计数变量的修改方法，如果从大到小就是递减，从小
到大就是递增。在修改了前面的初值和循环条件后，一定要检查计数变量变化
方式
6.strcpy()后不需要在最后一个字符前添加'\0'；读取字符串前不需要使用
memset置零；减法时不必将字符数组转换成整型数组再计算
7.三种方案的区别主要在于对字符串大小的比较方式上：
方案一：使用strcmp。出现WA的原因在于tmp_length定义成了char
方案二：使用数字的规律。出现WA的原因有两点。一点是tmp_length定义成了
		char，另一点是Line 82的k++写成了i++，一方面出现了不一致问题，
		另一方面修改了变量i的值从而导致错误
方案三：使用大数减法。出现WA的原因有两点。一点是tmp_length定义成了
		char，另一点是使用result判断而result极易溢出
*********************************************************************/