#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	string s;
	while (getline(cin, s))
	{
		reverse(s.begin(), s.end());
		auto start = s.begin();
		while (start != s.end())
		{
			auto end = start;
			while (end != s.end() && *end != ' ')
			{
				end++;
			}
			reverse(start, end);
			if (end != s.end())
			{
				start = end + 1;
			}
			else start = end;
		}
		cout << s << endl;
	}
	return 0;
}



//È¡ÇÉ
/*
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	string s1,s2;
	cin>>s2;
	while(cin>>s1)
	{
		s2 = s1+' '+s2;
	}
	cout<<s2<<endl;

	return 0;
}
*/