#include <iostream>

using namespace std;
int add1(int a, int b)
{
	int x, y;
	while (b != 0)
	{
		x = a ^ b;
		y = (a&b) << 1;
		a = x;
		b = y;
		
	}
	return a;
}
int main1()
{
	cout << add1(33, 78) << endl;
	return 0;
}