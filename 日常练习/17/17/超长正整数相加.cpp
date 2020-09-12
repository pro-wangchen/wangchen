#include <iostream>
#include <string>

using namespace std;
string adds(string n1, string n2)
{
	int len1 = n1.size();
	int len2 = n2.size();
	int cha = abs(len1 - len2);
	int longsize = len1 > len2 ? len1 : len2;
	if (len1 > len2)
	{
		n2.insert(0, cha, '0');
	}
	else if (len1 < len2)
	{
		n1.insert(0, cha, '0');
	}
	string ret;
	ret.resize(longsize);
	int flag = 0;
	for (int i = longsize - 1; i >= 0; i--)
	{
		ret[i] = (n1[i] - '0') + (n2[i] - '0') + flag;
		ret[i] += '0';
		if (ret[i] > '9')
		{
			ret[i] -= 10;
			flag = 1;
		}
		else flag = 0;

	}
	if (flag == 1)
	{
		ret.insert(0, 1, '1');
	}
	return ret;
}
int main()
{
	string n1, n2;
	while (cin >> n1 >> n2)
	{
		cout << adds(n1, n2) << endl;
	}
	return 0;
}