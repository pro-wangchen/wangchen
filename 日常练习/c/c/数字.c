#include <stdio.h>


//������A�е����ݺ�����B�е����ݽ��н�����������һ���� 
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
// ����1 / 1 - 1 / 2 + 1 / 3 - 1 / 4 + 1 / 5 ���� + 1 / 99 - 1 / 100 ��ֵ��
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
// ��д������һ�� 1�� 100 �����������г��ֶ��ٴ�����9��

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
//���0��999֮������С�ˮ�ɻ������������
//��ˮ�ɻ�������ָһ����λ�������λ���ֵ�������ȷ�õ��ڸ��������磻153��1��5��3 ? ��
//��153��һ����ˮ�ɻ�������
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