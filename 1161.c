/********1161******************************************************
题目描述：
Harmony is indispensible in our daily life and no one can live without it
----may be Facer is the only exception. One day it is rumored that repeat 
painting will create harmony and then hundreds of people started their endless drawing. 
Their paintings were based on a small template and a simple method of duplicating. 
Though Facer can easily imagine the style of the whole picture, 
but he cannot find the essential harmony. Now you need to help Facer by showing the picture on computer.
You will be given a template containing only one kind of character and spaces, 
and the template shows how the endless picture is created
----use the characters as basic elements and put them in the right position to form a bigger template, 
and then repeat and repeat doing that. Here is an example.
# #
 #      <-template
# #
So the Level 1 picture will be
# #
 #
# #
Level 2 picture will be
# #     # #
 #         #
# #     # #
     # #   
      #    
     # #   
# #    # #
 #        # 
# #    # #
输入：
The input contains multiple test cases.
The first line of each case is an integer N, 
representing the size of the template is N*N (N could only be 3, 4 or 5).
Next N lines describe the template.
The following line contains an integer Q, which is the Scale Level of the picture.
Input is ended with a case of N=0.
It is guaranteed that the size of one picture will not exceed 3000*3000.
输出：
For each test case, just print the Level Q picture by using the given template.
样例输入：
3
# #
 # 
# #
1
3
# #
 # 
# #
3
4
 OO 
O  O
O  O
 OO 
2
0
样例输出：
# #
 # 
# #
# #   # #         # #   # #
 #     #           #     # 
# #   # #         # #   # #
   # #               # #   
    #                 #    
   # #               # #   
# #   # #         # #   # #
 #     #           #     # 
# #   # #         # #   # #
         # #   # #         
          #     #          
         # #   # #         
            # #            
             #             
            # #            
         # #   # #         
          #     #          
         # #   # #         
# #   # #         # #   # #
 #     #           #     # 
# #   # #         # #   # #
   # #               # #   
    #                 #    
   # #               # #   
# #   # #         # #   # #
 #     #           #     # 
# #   # #         # #   # #
     OO  OO     
    O  OO  O    
    O  OO  O    
     OO  OO     
 OO          OO 
O  O        O  O
O  O        O  O
 OO          OO 
 OO          OO 
O  O        O  O
O  O        O  O
 OO          OO 
     OO  OO     
    O  OO  O    
    O  OO  O    
     OO  OO     
**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

char icon[2][3001][3001];
char initc[6][6];

int main(void){
	int N, Q;
	int i, j, r, s, q;
	int length;
	char c;
	char space = ' ';
	while(scanf("%d", &N) != EOF){
		getchar();
		if( N ==0 )
			break;
		for(i=1; i<=N; i++){
			for(j=1; j<=N; j++){
				scanf("%c", &icon[0][i][j]);
				if(icon[0][i][j] != ' ')
					c=icon[0][i][j];
			}
			getchar();  //去掉换行符
		}
		scanf("%d", &Q);
		getchar();
		for(i=1; i<=N; i++)
			for(j=1; j<=N; j++)
				initc[i][j] = icon[0][i][j];
		length = pow(N, Q);
		if(Q == 1){
			for(i=1; i<=N; i++){
				for(j=1; j<=N; j++)
					printf("%c", icon[0][i][j]);
				printf("\n");
			}
		}
		else{
			for(q=1; q<=Q-1; q++){
				int len = pow(N, q);
				for(i=1; i<=N; i++)
					for(j=1; j<=N; j++)
						if(initc[i][j]==c)
							for(r=1; r<=len; r++)
								for(s=1; s<=len; s++)
									if(icon[(q+1)%2][r][s]==c)
										icon[(q+2)%2][r+len*(i-1)][s+len*(j-1)]=c;
				for(i=1; i<=len; i++)
					for(j=1; j<=len; j++)
						icon[(q+1)%2][i][j]='\0';
			}
			for(i=1; i<=length; i++){
				for(j=1; j<=length; j++)
					if(icon[(Q+1)%2][i][j] == c)
						printf("%c", c);
					else
						printf(" ");
				printf("\n");
			}
		}
	}
	return 0;
}

/*************************************************************************
有两个问题需要注意：
1.空间问题。根据题意最多可能会出现Q=7的情况，如果以3001*3001（这里为了方便
计数，数组从[1][1]开始存储）的二维数组存储，每种情况安排一个这样的数组，一
方面产生大量浪费，另一方面超出了空间的限制。不妨只使用两个数组，使用求余运
算在两个数组间转换，每次由前一次的结果产生了新结果后，就将前一次结果所在的
数组清空，供下一次使用，两个数组轮换。最后打印最后一次保存的数组即可。但有
一个问题值得注意，还需设置一个数组存储原始图案，由于图案最大为5x5，因此只需
设置[6][6]数组即可。
2.保留原始图案。这里涉及到由前一次图案进行扩展得到新图案的方法问题。之前提
交显示runtime error的核心原因就是数组越界。由前一个图案的点(x,y)，在新图案
中的位置为(x+len*(i-1), y+len*(j-1))，这里的i, j确定的是移动的方位，即相对
于二维数组坐标原点(1, 1)的距离方位，这个方位应该是原始图案中的相对比例的距
离和方位，而不是前一个图案中的长度比例的方位，如果循环中带入的i, j是前一次
图案的值，则扩展的图案是按前一次的图案扩展，而不是按原始的扩展，这样也会导
致比例越来越大，最终出现数组越界。
3.每次保存的图案中其实有两个符号，即输入的可见符号和空格符，因此输入输出应
该严格按照NxN进行，非可见符即空格符。
**************************************************************************/