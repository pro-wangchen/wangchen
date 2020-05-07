#include <iostream>

using namespace std;
bool isPerfect(int n)
{
	int sum = 0;
	for (int i = 1; i <= n / 2; i++)
	{
		if (n%i == 0) sum += i;
	}
	if (sum == n) return true;
	else return false;
}
int main()
{
	int n;
	while (cin >> n)
	{
		int count = 0;
		for (int i = 1; i <= n; i++)
		{
			if (isPerfect(i)) count++;
		}
		cout << count << endl;
	}
}