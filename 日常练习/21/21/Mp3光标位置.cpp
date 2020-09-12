#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n;
	string str;
	while (cin >> n >> str)
	{
		int cursor = 1, first = 1;
		if (n <= 4)
		{
			for (int i = 0; i < str.size(); i++)
			{
				if (cursor == 1 && str[i] == 'U') cursor = n;
				else if (cursor == n && str[i] == 'D') cursor = 1;
				else if (str[i] == 'U') cursor--;
				else cursor++;
			}
			for (int i = 1; i < n; i++)
			{
				cout << i << " ";
			}
			cout << n << endl;
			cout << cursor << endl;
		}
		else
		{
			for (int i = 0; i < str.size(); i++)
			{
				if (cursor == 1 && first == 1 && str[i] == 'U')
				{
					first = n - 3;
					cursor = n;
				}
				else if (cursor == n && first == n - 3 && str[i] == 'D')
				{
					first = 1;
					cursor = 1;
				}
				else if (first != 1 && cursor == first && str[i] == 'U')
				{
					first--;
					cursor--;
				}
				else if (first != n - 3 && cursor == first + 3 && str[i] == 'D')
				{
					first++;
					cursor++;
				}
				else if (str[i] == 'U') cursor--;
				else cursor++;
			}
			for (int i = first; i < first + 3; i++)
			{
				cout << i << " ";
			}
			cout << first + 3 << endl;
			cout << cursor << endl;
		}

	}

	return 0;
}