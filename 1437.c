/**********1437*************************************************************
题目描述：
With highways available, driving a car from Hangzhou to any other city is easy. 
But since the tank capacity of a car is limited, we have to find gas stations 
on the way from time to time. Different gas station may give different price. 
You are asked to carefully design the cheapest route to go.
输入：
For each case, the first line contains 4 positive numbers: Cmax (<= 100), 
the maximum capacity of the tank; D (<=30000), the distance between Hangzhou 
and the destination city; Davg (<=20), the average distance per unit gas that 
the car can run; and N (<= 500), the total number of gas stations. 
Then N lines follow, each contains a pair of non-negative numbers: 
Pi, the unit gas price, and Di (<=D), the distance between this station and Hangzhou, 
for i=1,...N. All the numbers in a line are separated by a space.
输出：
For each test case, print the cheapest price in a line, accurate up to 2 decimal places. 
It is assumed that the tank is empty at the beginning. 
If it is impossible to reach the destination, print 
"The maximum travel distance = X" where X is the maximum possible distance the car can run, 
accurate up to 2 decimal places.
样例输入：
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300
50 1300 12 2
7.10 0
7.00 600
样例输出：
749.17
The maximum travel distance = 1200.00
**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

struct station
{
	float pi;
	int di;
}gas[501];

void swap(int i, int j){
	float tmp_pi = gas[i].pi;
	int tmp_di = gas[i].di;
	(gas+i)->pi = (gas+j)->pi;
	(gas+i)->di = (gas+j)->di;
	(gas+j)->pi = tmp_pi;
	(gas+j)->di = tmp_di;
}

void quicksort(int left, int right){
	if(left > right)
		return;
	int i = left;
	int j = right;
	int temp = gas[left].di;

	while(i != j){
		while(gas[j].di>=temp && i<j)
			j--;
		while(gas[i].di<=temp && i<j)
			i++;
		if(i<j)
			swap(i, j);
	}

	swap(left, i);
	quicksort(left, i-1);
	quicksort(i+1, right);
}

int main(void){
	int cmax, D, Davg, N;
	int distance;
	int i, no, mini;
	int flag, result;
	float dmax, dleft, min, cost, price, maxdistance;
	while(scanf("%d %d %d %d", &cmax, &D, &Davg, &N) != EOF){
		if(N == 0){
			printf("The maximum travel distance = 0.00\n");
			continue;
		}
		for(i=0; i<N; i++)
			scanf("%f %d", &gas[i].pi, &gas[i].di);
		quicksort(0, N-1);
		if(gas[0].di != 0){
			printf("The maximum travel distance = 0.00\n");
			continue;
		}
		dmax = cmax * Davg;
		dleft = 0;
		no = 0;
		cost = 0;
		price = gas[0].pi;
		distance = 0;
		maxdistance = 0;
		if(N==1){
			if(dmax >= D )
				printf("%.2f\n", D*price/Davg);
			else
				printf("The maximum travel distance = %.2f\n", dmax);
			continue;
		}
		while(no<N-1){
			i = no+1;
			mini = no+1;
			min = 1000;
			flag = 0;
			if(gas[i].di-distance>dmax){
				maxdistance = distance + dmax;
				result = 0;
				break;
			}
			while((gas[i].di-distance)<=dmax && i<N){
				if(gas[i].pi < gas[no].pi){
					flag = 1;
					break;
				}
				else{
					if(gas[i].pi <= min){
						min = gas[i].pi;
						mini = i;
					}
				}
				i++;
			}
			if(flag==1){
				if(i<N-1){
					cost += price * (gas[i].di - distance - dleft);
					no = i;
					price = gas[i].pi;
					distance = gas[i].di;
					dleft = 0;
					continue;
				}
				else{
					if(gas[i].di+dmax>=D){
						cost = cost + price*(gas[i].di-distance-dleft) + gas[i].pi*(D-gas[i].di);
						result = 1;
						break;
					}
					else{
						maxdistance = gas[i].di + dmax;
						result = 0;
						break;
					}
				}
			}
			else{
				if(distance+dmax>=D){
					cost += price * (D - distance - dleft);
					result = 1;
					break;
				}
				else{
					if(mini<N-1){
						cost += price * (dmax - dleft);
						no = mini;
						price = gas[mini].pi;
						dleft = dmax - (gas[mini].di - distance);
						distance = gas[mini].di;
						continue;
					}
					else{
						if(gas[mini].di+dmax>=D){
							cost = cost+price*(dmax-dleft)+gas[mini].pi*(D-dmax-distance);
							result = 1;
							break;
						}
						else{
							maxdistance = gas[mini].di + dmax;
							result = 0;
							break;
						}
					}
				}
			}
		}
		if(result == 1)
			printf("%.2f\n", cost/Davg);
		else
			printf("The maximum travel distance = %.2f\n", maxdistance);
	}
	return 0;
}

/***********************************************************
1.这个问题使用贪心算法解决，算法的基本策略不算难，在加油站按
里程升序排列后，主要有两点策略：在油箱满油情况下可行驶范围内
（1）从当前加油站顺序往后查找，如果有加油站的价格比当前所在
加油站的价格低，在当前加油站加油至刚好可以行驶到这第一个价格
更低的站点。注意两个关键词：顺序往后第一个就停止，价格更低
（是小于而不是小于等于，否则会因为查找到等于的就漏掉了后面的
小于的Line 122）
（2）如果满油可行驶范围内没有更小的，则选择在后续的站点里最小
的那个，将油箱加满行驶到那个站点。这里要注意如果最小的有多个，
则任意选择一个即可（因此可以用小于等于）
2.细节问题：要注意到每次加油前油箱内可能会有剩余的油，在做计
算时一定要考虑进去。特别是由当前站点往后找不到价格更低的情况
时策略是加满油，这样在到达下一个站点时极大可能是油箱有剩余油
（如Line 158就出现过这样的错误）
3.数据更新问题：一个问题是初始化，在一次循环结束后一些关键的
数据要重新初始化，特别要注意定义在循环体外面的变量，如果没有
考虑这一点，可能在新的循环中该值为前一次的旧值，从而出错（如
Line 103变量maxdistance的重新初始化）；另一个问题是在更新和
计算数据时，如果用到的数据也在这一次要更新，则该数据应该在所
有使用完成后在更新，否则也会出现新值、旧值的使用问题错误（如
Line 167中distance必须在dleft计算后才可以更新）
4.算法的细节问题：例如该题中必须考虑7种可能的情况，如代码中
的if-else语句判断所示，而有5种与结束有关，只有两种涉及到贪心
算法的继续，因此例如如何结束、如何循环等这些在写代码前必须
考虑清楚
5.临界情况问题：本题中出现的临界情况就很多，这些也应该在
开始写代码前设计算法时考虑清楚。例如如果没有加油站（Line 86）
，题目前提是油箱为空如果第一个加油站距离不是0（Line 93），如
果只在起点0有一个加油站（Line 104），如果当前加油站紧接着的
后一个加油站与它的距离比满油的最大距离还要大（Line 116）等等
6.关于复杂度问题：这道题提交时出现了runtime error和Time limit
问题。在循环时要注意循环条件最好是可计数的（如Line 111，之前是
distance < D）这样不容易出现死循环；另外判断条件如果是&&连接的
那么从左到右判断的话只要出现不符合的就直接停止，因此尽量把复
杂度小的循环次数少的等条件放在左边（如Line 121）；还有就是对
与复合的if-else语句尽量把相同的条件提到最外面的大if里面，这样
比if-else if-else if……要减少很多重复的判断和计算
************************************************************/