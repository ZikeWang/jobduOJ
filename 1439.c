/**********1439***********************************************************
题目描述：
The least common multiple (LCM) of a set of positive integers is the 
smallest positive integer which is divisible by all the numbers in the set. 
For example, the LCM of 5, 7 and 15 is 105.
输入：
Input will consist of multiple problem instances. The first line of the 
input will contain a single integer indicating the number of problem 
instances. Each instance will consist of a single line of the form 
m n1 n2 n3 ... nm where m is the number of integers in the set and n1 ... nm 
are the integers. All integers will be positive and lie within the range 
of a 32-bit integer.
输出：
For each problem instance, output a single line containing the corresponding LCM. 
All results will lie in the range of a 32-bit integer.
样例输入：
2
3 5 7 15
6 4 10296 936 1287 792 1
样例输出：
105
10296
**************************************************************************/

#include <stdio.h>
#include <string.h>

int gcd(int a, int b){
	int tmp;
	while(b != 0){
		tmp = a;
		a = b;
		b = tmp % b;
	}
	return a;
}

/*
int gcd(int a, int b){
	return b==0 ? a : gcd(b, a%b);
}
*/

int main(void){
	int N, cnt;
	long int a, result;
	int i;
	while(scanf("%d", &N) != EOF){
		while(N != 0){
			result = 1;
			scanf("%d", &cnt);
			for(i=0; i<cnt; i++){
				scanf("%ld", &a);
				result = result / gcd(result, a)  * a;
			}
			printf("%ld\n", result);
			N--;
		}
	}
	return 0;
}

/***********************************************************************
有几个问题要注意：
1.提交时出现wrong answer，问题主要在两个方面：
（1）要看清题目要求，特别是输入输出的要求。题目要求是
Input will consist of multiple problem instances. The first line of the 
input will contain a single integer indicating the number of problem 
instances.也就是说有多组大的测试用例，每组大的案例的第一行是该组后面小的
测试用例的个数，而不是第一行的N是总用例的数目。
（2）输入和输出的格式转换符要一致。本题提交时的另一个WA问题就出在前面定义
的是long，后面读取和输出的是int，这样很可能造成bit的丢失
2.要注意题目数据的范围，考虑数据定义时选用的类型是否合适（例如本题中如果
定义过小采用int很可能造成溢出问题），数据是否是大数而不能使用常规的输入
3.Time Limit Exceed：经验表明很多情况下不采用明确的例如有循环次数控制的
数据读入方式，而选用例如采用(c=getchar()) != '\n'的判断条件来控制输入流的
读取，很可能发生超时
4.runtime error：如果用一个数组存每个小测试用例中的所有数字，如果数组定义
小了很可能最后越界，所以采用提交代码中用int类型的cnt进行计数，每次叠加计算
而避免在数组中存取，可以较好避免这类问题
************************************************************************/