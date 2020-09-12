#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N;
	while (cin >> N)
	{
		vector<int> a;
		a.resize(N + 1);
		a[N] = 0;

		for (int i = 0; i < N; i++)
		{
			cin >> a[i];
		}
		int count = 0;
		int i = 0;
		while (i < N)
		{
			if (a[i] < a[i + 1])
			{
				while (i < N&&a[i] <= a[i + 1])
				{
					i++;
				}
				i++;
				count++;
			}
			else if (a[i] > a[i + 1])
			{
				while (i < N&& a[i] >= a[i + 1])
				{
					i++;
				}
				i++;
				count++;
			}
			else
			{
				i++;
			}
		}
		cout << count << endl;
	}
	return 0;
}