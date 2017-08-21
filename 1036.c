/*********************************1036************************************
题目描述：
    Among grandfather's papers a bill was found.
    72 turkeys $_679_
    The first and the last digits of the number that obviously represented
    the total price of those turkeys are replaced here by blanks (denoted _), 
    for they are faded and are illegible. What are the two faded digits and 
    what was the price of one turkey?
    We want to write a program that solves a general version of the above 
    problem.
    N turkeys $_XYZ_
    The total number of turkeys, N, is between 1 and 99, including both. 
    The total price originally consisted of five digits, but we can see 
    only the three digits in the middle. We assume that the first digit 
    is nonzero, that the price of one turkeys is an integer number of 
    dollars, and that all the turkeys cost the same price.
    Given N, X, Y, and Z, write a program that guesses the two faded digits 
    and the original price. In case that there is more than one candidate 
    for the original price, the output should be the most expensive one. 
    That is, the program is to report the two faded digits and the maximum 
    price per turkey for the turkeys.
输入：
    The first line of the input file contains an integer N (0<N<100), which 
    represents the number of turkeys. In the following line, there are the 
    three decimal digits X, Y, and Z., separated by a space, of the original 
    price $_XYZ_.
输出：
    For each case, output the two faded digits and the maximum price per 
    turkey for the turkeys.
样例输入：
72
6 7 9
5
2 3 7
78
0 0 5
样例输出：
3 2 511
9 5 18475
0
**************************************************************************/

#include <stdio.h>

int main(){
	int n, x, y, z;
	int i, j, a, b, sum, price;
	while(scanf("%d", &n) != EOF){
		scanf("%d %d %d", &x, &y, &z);
		price = 0;
		for(i=1; i<=9; i++)
			for(j=0; j<=9; j++){
				sum = i*10000 + x*1000 + y*100 + z*10 + j;
				if(sum % n == 0 && sum / n > price){
					a = i;
					b = j;
					price = sum / n;
				}
			}
		if(price)
			printf("%d %d %d\n", a, b, price);
		else
			printf("0\n");
	}

	return 0;
}
