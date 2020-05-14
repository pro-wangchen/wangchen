#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int calD(string a, string b)
{
	if (a.empty() || b.empty())
	{
		return max(a.size(), b.size());
	}
	int len1 = a.size();
	int len2 = b.size();
	vector<vector<int>> arr(1 + len1, vector<int>(1 + len2, 0));
	for (int i = 0; i <= len1; i++)
	{
		arr[i][0] = i;
	}
	for (int i = 0; i <= len2; i++)
	{
		arr[0][i] = i;
	}
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (a[i - 1] == b[j - 1])
			{
				arr[i][j] = 1 + min(arr[i - 1][j], arr[i][j - 1]);
				arr[i][j] = min(arr[i][j], arr[i - 1][j - 1]);
			}
			else
			{
				arr[i][j] = 1 + min(arr[i - 1][j], arr[i][j - 1]);
				arr[i][j] = min(arr[i][j], arr[i - 1][j - 1] + 1);
			}
		}

	}
	return arr[len1][len2];

}
int main()
{
	string a, b;
	while (cin >> a >> b)
	{
		cout << calD(a, b) << endl;
	}

	return 0;
}