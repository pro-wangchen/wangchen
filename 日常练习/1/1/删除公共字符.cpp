//¹şÏ£Ó³Éä
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	int hash[256] = { 0 };
	for (int i = 0; i < s2.size(); i++)
	{
		hash[s2[i]]++;
	}
	string ret;
	for (int i = 0; i < s1.size(); i++)
	{
		if (hash[s1[i]] == 0)
		{
			ret += s1[i];
		}
	}
	cout << ret << endl;

	return 0;
}



//±¬ËÑ
/*
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);

	for (int i = 0; i < s1.size(); i++)
	{
		if (s2.find(s1[i]) == -1)
		{
			cout << s1[i];
		}
	}


	return 0;
}*/