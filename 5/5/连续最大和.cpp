//һ�������� N ��Ԫ�أ�����������������͡� ���磺[-1, 2, 1]������������������Ϊ[2, 1]�����Ϊ 3
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	int sum = 0;
	int max = -100000;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
		if (sum > max)
		{
			max = sum;
		}
		if (sum < 0)
		{
			sum = 0;
		}
	}
	cout << max << endl;

	return 0;
}