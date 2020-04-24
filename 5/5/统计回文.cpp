#include <iostream>
#include <string>

using namespace std;

bool palindrome(const string& s)
{
	int begin = 0;
	int end = s.size() - 1;
	while (begin < end)
	{
		if (s[begin] != s[end])
			return false;
		begin++;
		end--;
	}
	return true;
}
int main()
{
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	int count = 0;
	for (int i = 0; i <= s1.size(); i++)
	{
		string s = s1;
		s.insert(i, s2);
		if (palindrome(s))
		{
			count++;
		}
	}
	cout << count << endl;

	return 0;
}