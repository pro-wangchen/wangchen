#include <iostream>


using namespace std;

int main()
{
	int q, w, e, r;
	int a, b1, b2, c;
	cin >> q >> w >> e >> r;
	a = (q + e) / 2;
	c = (r - w) / 2;
	b1 = a - q;
	b2 = r - c;
	if (b1 == b2)
	{
		cout << a << ' ' << b1 << ' ' << c << endl;
	}
	else cout << "No" << endl;
	return 0;
}