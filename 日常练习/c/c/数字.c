#include <stdio.h>


//将数组A中的内容和数组B中的内容进行交换。（数组一样大） 
void exchange(int A[],int B[])
{
	int tmp[] = { 0 };
	int size = sizeof(A)/sizeof(int);
	for (int i = 0; i < size; i++)
	{
		 tmp[i] = A[i];
		 A[i] = B[i];
		 B[i] = tmp[i];
	}
}
// 计算1 / 1 - 1 / 2 + 1 / 3 - 1 / 4 + 1 / 5 …… + 1 / 99 - 1 / 100 的值。
double data()
{
	double n = 1;
	double sum = 0;
	for (int i = 1; i <= 100; i++)
	{
		sum += n / i;
		n *=-1;
	}
	return sum;
}
// 编写程序数一下 1到 100 的所有整数中出现多少次数字9。

int num(int n,int x)
{
	int count = 0;
	for (int i = 1; i <= n; i++)
	{
		int tmp = i;
		if (tmp)
		{
			if (tmp % 10 == x)
			{
				count++;
			}
			tmp /= 10;
		}
	}
	return count;
}
//求出0～999之间的所有“水仙花数”并输出。
//“水仙花数”是指一个三位数，其各位数字的立方和确好等于该数本身，如；153＝1＋5＋3 ? ，
//则153是一个“水仙花数”。
void print()
{
	for (int i = 0; i < 1000; i++)
	{
		int first = i % 10;
		int second = i / 10 % 10;
		int third = i / 100;
		int x = first * first*first + second * second*second + third * third*third;
		if (x == i)
		{
			printf("%d ", i);
		}
	}
}
int main1()
{
	
	return 0;
}