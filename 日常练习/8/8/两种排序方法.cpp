#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
	int n;
	while (cin >> n)
	{
		bool flag1 = 0, flag2 = 0;
		vector<string>  str(n);
		for (auto &i : str)
			cin >> i;
		for (int i = 1; i < str.size(); i++)
		{
			if (flag1 == 0 && str[i - 1] > str[i])
				flag1 = 1;
			if (flag2 == 0 && str[i - 1].size() > str[i].size())
				flag2 = 1;
			if (flag1&&flag2)
				break;
		}
		if (flag1 == 0 && flag2 == 0)
			cout << "both" << endl;
		else if (flag1 == 0)
			cout << "lexicographically" << endl;
		else if (flag2 == 0)
			cout << "lengths" << endl;
		else
			cout << "none" << endl;
	}
	return 0;
}