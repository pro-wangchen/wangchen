//±©ËÑ
/*
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int A, B;
	cin >> A >> B;
	int i = max(A, B);
	while (1)
	{
		if (i%A == 0 && i%B == 0) break;
		i++;
	}
	cout << i << endl;
	return 0;
}
*/

//Õ·×ªÏà³ý·¨
#include <iostream>

using namespace std;
int gcd(int a, int b)
{
	int r;
	while (r = a % b)
	{
		a = b;
		b = r;
	}
	return b;
}
int main()
{
	int A, B;
	cin >> A >> B;
	cout << A * B / gcd(A, B) << endl;
	return 0;
}