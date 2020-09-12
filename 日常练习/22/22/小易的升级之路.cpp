#include <iostream>
#include <vector>
using namespace std;
int gcd(int a, int b)
{
	int r;
	while (r = a % b)
	{
		a = b;
		b = r;
	}
	return b;
}
int main()
{
	int n, a;
	while (cin >> n >> a)
	{
		int tmp;
		for (int i = 0; i < n; i++)
		{
			cin >> tmp;
			if (a >= tmp) a += tmp;
			else a += gcd(a, tmp);
		}

		cout << a << endl;
	}

	return 0;
}