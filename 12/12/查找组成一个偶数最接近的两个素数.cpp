#include <iostream>
#include <algorithm>
using namespace std;

bool isprime(int a)
{
	if (a == 1 || a == 2) return false;
	if (a % 2 == 0) return false;
	int k = sqrt(a);
	for (int i = 3; i <= k; i+=2)
	{
		if (a % i == 0) return false;
	}
	return true;
}

int main()
{
	int n;
	cin >> n;
	int k = n / 2;
	int low = k, high = k;
	while (1)
	{
		if (isprime(low) && isprime(high))
		{
			cout << low << endl << high << endl;

			break;
		}
		low--;
		high++;

	}
	return 0;
}