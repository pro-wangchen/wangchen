#include <iostream>
#include <string>
using namespace std;
bool compare(const char * n1, const char * n2)
{
	if (*n1 == '\0'&& *n2 == '\0') return true;
	if (*n1 == '\0' || *n2 == '\0') return false;
	if (*n1 == '?') return compare(n1 + 1, n2 + 1);
	else if (*n1 == *n2) return compare(n1 + 1, n2 + 1);
	else if (*n1 == '*') return compare(n1 + 1, n2) || compare(n1, n2 + 1) || compare(n1 + 1, n2 + 1);
	return false;
}

int main()
{
	string n1, n2;
	while (cin >> n1 >> n2)
	{
		bool ret = compare(n1.c_str(), n2.c_str());
		if (ret) cout << "true" << endl;
		else cout << "false" << endl;
	}

	return 0;
}