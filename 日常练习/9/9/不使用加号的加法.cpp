#include <iostream>
using namespace std;


int addAB(int A, int B)
{
	int x, y;
	while (B != 0)
	{
		x = A ^ B;
		y = (A&B) << 1;
		A = x;
		B = y;
	}
	return A;
}

int main()
{

	cout << addAB(5, 3) << endl;
	return 0;
}