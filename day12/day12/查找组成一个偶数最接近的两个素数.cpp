//任意一个偶数（大于2）都可以由2个素数组成，组成偶数的2个素数有很多种情况，
//本题目要求输出组成指定偶数的两个素数差值最小的素数对

#include <iostream>
#include <algorithm>
using namespace std;
bool isprime(int n)//判断是否是素数
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