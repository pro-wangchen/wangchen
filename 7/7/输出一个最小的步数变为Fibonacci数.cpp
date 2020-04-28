#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
	int N;
	cin >> N;
	int fb1 = 0, fb2 = 1, fb;
	int low, high;
	while (1)
	{
		fb = fb1 + fb2;
		fb1 = fb2;
		fb2 = fb;

		if (fb < N)
		{
			low = N - fb;
		}
		else
		{
			high = fb - N;
			break;
		}


	}
	cout << min(low, high) << endl;
	return 0;

}