#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a, b;
	while (cin >> a >> b)
	{
		if (a.size() > b.size())
		{
			swap(a, b);
		}
		string str_data;
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = i; j < a.size(); j++)
			{
				string tmp = a.substr(i, j - i + 1);
				if (int (b.find(tmp))<0)
				{
					break;
				}
				else if (tmp.size() > str_data.size())
				{
					str_data = tmp;
				}
			}
		}
		cout << str_data << endl;
	}

	return 0;
}