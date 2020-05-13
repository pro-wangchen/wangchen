#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a;
	while (cin>>a)
	{
		int hash[256] = { 0 };
		for (auto &i : a)
		{
			hash[i]++;
		}
		int i;
		for (i = 0; i < a.size(); i++)
		{
			if (hash[a[i]] == 1)
			{
				cout << a[i] << endl;
				break;
			}
		}
		if (i >= a.size()) cout << -1 << endl;
	}

	return 0;
}