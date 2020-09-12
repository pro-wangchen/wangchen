#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s, cur, res;
	getline(cin, s);
	for (int i = 0; i <= s.size(); i++)
	{
		if (s[i] <= '9'&&s[i] >= '0')
		{
			cur += s[i];
		}
		else
		{
			if (res.size() < cur.size())
			{
				res = cur;
			}
			else cur.clear();
		}
	}
	cout << res << endl;
	return 0;

}