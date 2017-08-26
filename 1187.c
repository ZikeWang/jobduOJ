/*********************************1187************************************
题目描述：
职工有职工号，姓名，年龄.输入n个职工的信息，找出3个年龄最小的职工打印出来。
输入：
输入第一行包括1个整数N，1<=N<=30，代表输入数据的个数。
接下来的N行有N个职工的信息：
包括职工号(整数)， 姓名(字符串，长度不超过10)， 年龄(1<=age<=100)。
输出：
可能有多组测试数据，对于每组数据，
输出结果行数为N和3的较小值，分别为年龄最小的职工的信息。
关键字顺序：年龄>工号>姓名，从小到大。
样例输入：
5
501 Jack 6
102 Nathon 100
599 Lily 79
923 Lucy 15
814 Mickle 65
样例输出：
501 Jack 6
923 Lucy 15
814 Mickle 65
**************************************************************************/

#include <stdio.h>
#include <string.h>

struct Worker
{
	int id;
	char name[11];
	int age;
}work[31];

void swap(int i, int j){
	int tmp_id = work[i].id;
	work[i].id = work[j].id;
	work[j].id = tmp_id;

	char tmp_name[11];
	strcpy(tmp_name, work[i].name);
	strcpy(work[i].name, work[j].name);
	strcpy(work[j].name, tmp_name);

	int tmp_age = work[i].age;
	work[i].age = work[j].age;
	work[j].age = tmp_age;
}

int main(void){
    int n;
    int i, j;
    while(scanf("%d", &n) != EOF){
    	for(i=0; i<n; i++){
    		scanf("%d %s %d", &work[i].id, work[i].name, &work[i].age);
    	}
    	for(i=0; i<n; i++)
    		for(j=0; j<n-1-i; j++){
    			if(work[j].age > work[j+1].age){
    				swap(j, j+1);
    			}
    			else if(work[j].age == work[j+1].age){
    				if(work[j].id > work[j+1].id){
    					swap(j, j+1);
    				}
    				else if(work[j].id == work[j+1].id){
    					if(strcmp(work[j].name, work[j+1].name) > 0){
    						swap(j, j+1);
    					}
    				}
    			}
    		}
    	if(n<3){
    		for(i=0; i<n; i++)
    			printf("%d %s %d\n", work[i].id, work[i].name, work[i].age);
    	}
    	else{
    		for(i=0; i<3; i++)
    			printf("%d %s %d\n", work[i].id, work[i].name, work[i].age);
    	}
    }
    return 0;
}