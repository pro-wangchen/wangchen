#include <iostream>
#include <algorithm>
using namespace std;

int main1()
{
	int fib = 1,fib1 = 1, fib2 = 1,  n;
	cin >> n;
	int l, r;
	if (n == 1)
	{
		cout << 0 << endl;
	}
	else
	{
		while (1)
		{
			fib2 = fib1;
			fib1 = fib;
			fib = fib1 + fib2;
			if (fib < n)
			{
				l = n - fib;
			}
			else
			{
				r = fib - n;
				break;
			}

		}
		cout << min(l, r) << endl;
	}
	return 0;
}