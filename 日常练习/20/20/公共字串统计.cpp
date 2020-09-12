#include <iostream>
#include <string>

using namespace std;
int lenstr(string s1, string s2)
{
	if (s1.size() > s2.size())
	{
		swap(s1, s2);
	}
	int count = 0, max = 0;
	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = i; j < s1.size(); j++)
		{
			string tmp = s1.substr(i, j - i + 1);
			if (int(s2.find(tmp)) > 0)
			{
				count = tmp.size();
			}
			if (count > max)
			{
				max = count;
			}
		}
	}
	return max;
}
int main()
{
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		cout << lenstr(s1, s2) << endl;
	}
	return 0;
}