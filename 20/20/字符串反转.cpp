#include <iostream>
#include <string>

using namespace std;

string rstr(string s)
{
	string tmp;
	for (int i = s.size() - 1; i >= 0; i--)
	{
		tmp.push_back(s[i]);
	}
	return tmp;
}
int main()
{
	string str;
	while (cin >> str)
	{
		cout << rstr(str) << endl;

	}
	return 0;
}