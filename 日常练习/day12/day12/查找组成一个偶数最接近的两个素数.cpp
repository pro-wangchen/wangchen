//����һ��ż��������2����������2��������ɣ����ż����2�������кܶ��������
//����ĿҪ��������ָ��ż��������������ֵ��С��������

#include <iostream>
#include <algorithm>
using namespace std;
bool isprime(int n)//�ж��Ƿ�������
{
	if (n == 1 || n == 2) return false;
	if (n % 2 == 0) return false;
	int sq = sqrt(n);
	for (int i = 3; i <= sq; i += 2)
	{
		if (n % i == 0) return false;
	}
	return true;
		
}
int main()
{
	int n;
	while (cin >> n)
	{

		int first = 0, scend = 0xfffffff;
		for (int i = 1; i < n; i++)
		{
			if (isprime(i) && isprime(n - i))
			{
				if (abs(n - i - i) < abs(first - scend))
				{
					first = i;
					scend = n - i;
				}
			}
		}
		cout << first << endl << scend << endl;
	}
	return 0;
}