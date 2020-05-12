#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;
		int num = 2 * n;
		vector<int> poker(num);
		for (int i = 0; i < num; i++)
		{
			cin >> poker[i];
		}
		while (k--)
		{
			vector<int> v(poker.begin(), poker.end());
			for (int i = 0; i < n; i++)
			{
				poker[2 * i] = v[i];
				poker[2 * i + 1] = v[i + n];
			}
		}
		for (int i = 0; i < num - 1; i++)
		{
			cout << poker[i] << " ";
		}
		cout << poker[num - 1] << endl;
	}
	return 0;
}