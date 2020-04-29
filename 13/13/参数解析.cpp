#include <iostream> 
#include <string>
#include <vector>
using namespace std;

int main()
{
	string s;
	while (getline(cin, s))
	{
		vector<string> v;
		string tmp = "";
		for (int i = 0; i < s.size(); i++)
		{
			int flag = -1;
			if (s[i] == '"')
			{
				flag *= -1;
			}
			if (s[i] == ' ' && flag == -1)
			{
				v.push_back(tmp);
				tmp = "";
			}
			else
			{
				tmp += s[i];
			}
		}
		v.push_back(tmp);
		cout << v.size() << endl;
		for (auto &i : v)
		{
			cout << i << endl;
		}
	}
	return 0;
}
