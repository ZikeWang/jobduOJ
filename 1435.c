/********1435*****************************************************
题目描述：
通过悬崖的yifenfei，又面临着幽谷的考验——
幽谷周围瘴气弥漫，静的可怕，隐约可见地上堆满了骷髅。
由于此处长年不见天日，导致空气中布满了毒素，
一旦吸入体内，便会全身溃烂而死。
幸好yifenfei早有防备，提前备好了解药材料（各种浓度的万能药水）。
现在只需按照配置成不同比例的浓度。
现已知yifenfei随身携带有n种浓度的万能药水，体积V都相同，浓度则分别为Pi%。
并且知道，针对当时幽谷的瘴气情况，只需选择部分或者全部的万能药水，
然后配置出浓度不大于 W%的药水即可解毒。
现在的问题是：如何配置此药，能得到最大体积的当前可用的解药呢？
特别说明：由于幽谷内设备的限制,只允许把一种已有的药全部混入另一种之中
（即：不能出现对一种药只取它的一部分这样的操作）。
输入：
输入数据的第一行是一个整数C，表示测试数据的组数；
每组测试数据包含2行，首先一行给出三个正整数n,V,W(1<=n,V,W<=100)；
接着一行是n个整数，表示n种药水的浓度Pi%(1<=Pi<=100)。
输出：
对于每组测试数据，请输出一个整数和一个浮点数；
其中整数表示解药的最大体积，浮点数表示解药的浓度(四舍五入保留2位小数)；
如果不能配出满足要求的的解药，则请输出0 0.00。
样例输入：
3
1 100 10
100
2 100 24
20 30
3 100 24
20 20 30
样例输出：
0 0.00
100 0.20
300 0.23
******************************************************************/

#include <stdio.h>

void quicksort(int *a, int left, int right){
	if(left > right)
		return;
	int i = left;
	int j = right;
	int temp = *(a+left);
	while(i != j){
		while(a[j]>=temp && i<j)
			j--;
		while(a[i]<=temp && i<j)
			i++;
		if(i<j){
			int tmp = *(a+i);
			*(a+i) = *(a+j);
			*(a+j) = tmp;
		}
	}
	*(a+left) = *(a+i);
	*(a+i) = temp;
	quicksort(a,left,i-1);
	quicksort(a,i+1,right);
}

int main(void){
	int C, n, V, W, pi[100];
	float pi_total, pi_back;
	int v_total, v_back;
	int i = 1;
	int j = 0;
	scanf("%d", &C);
	while(C-- > 0){
		for(j=0; j<100; j++)
			pi[j] = 0;
		i = 1;
		scanf("%d %d %d", &n, &V, &W);
		for(j=0; j<n; j++)
			scanf("%d", pi+j);
		quicksort(pi, 0, n-1);
		pi_total = *pi;
		v_total = V;
		pi_back = pi_total;
		v_back = v_total;
		while(pi_total<=W && i<n){
			pi_back = pi_total;
			v_back = v_total;
			pi_total = (pi_total*v_total+pi[i++]*V)/(v_total+V);
			v_total += V;
		}
		if(pi_total > W && pi_back <= W)
			printf("%d %.2f\n", v_back, pi_back/100);
		else if(pi_total <= W )
			printf("%d %.2f\n", v_total, pi_total/100);
		else
			printf("0 0.00\n");
	}
	return 0;
}

/********1435*****************************************************
注意判断条件，一方面要满足浓度方面的问题，另一方面要满足数组是否
遍历完了，在贪心循环的过程中以及循环后选择打印的过程中都应注意这
两方面因素
******************************************************************/