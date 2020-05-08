/*
杨辉三角
让第n行的第一个和最后一个都为1
其他的遵循 a[i][j] = a[i-1][j-1]+a[i-1][j]+a[i-1][j+1]
*/
#include <iostream>
#include <vector>
using namespace std;
void print(int n)
{
	vector<vector<int>> a(n, vector<int>(2 * n - 1, 0));
	a[0][n - 1] = a[n - 1][0] = a[n - 1][2 * n - 2] = 1;
	if (n < 2)
	{
		cout << "-1" << endl;
		return;
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < 2 * n - 2; j++)
		{
			a[i][j] = a[i - 1][j] + a[i - 1][j - 1] + a[i - 1][j + 1];
		}
	}
	for (int i = 0; i < 2 * n - 1; i++)
	{
		if (a[n - 1][i] != 0 && (a[n - 1][i]) % 2 == 0)
		{
			cout << i + 1 << endl;
			return;
		}
	}
	return;
}
int main()
{
	int n;
	while (cin >> n)
	{
		print(n);
	}

	return 0;
}