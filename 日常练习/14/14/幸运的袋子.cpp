#include <iostream>
#include <algorithm>

using namespace std;

int luckyBag(int x[], int pos, int n, int sum, int multi)
{
	int count = 0;
	for (int i = pos; i < n; i++)
	{
		sum += x[i];
		multi *= x[i];
		if (sum > multi)
		{
			count += 1 + luckyBag(x, i + 1, n, sum, multi);

		}
		else if (x[i] == 1)
		{
			count += luckyBag(x, i + 1, n, sum, multi);
		}
		else break;
		sum -= x[i];
		multi /= x[i];
		while (i < n - 1 && x[i] == x[i + 1]) i++;
	}
	return count;
}

int main()
{
	int n;
	while (cin >> n)
	{
		int x[n];
		for (int i = 0; i < n; i++)
		{
			cin >> x[i];
		}
		sort(x, x + n);
		cout << luckyBag(x, 0, n, 0, 1) << endl;
	}
	return 0;
}