#include <iostream>

using namespace std;
int box(int n, int m)
{
	if (n*m == 0)
	{
		return 1;
	}
	else return box(n - 1, m) + box(n, m - 1);
}
int main()
{
	int a, b;
	while (cin >> a >> b)
	{
		cout << box(a, b) << endl;
	}

	return 0;
}