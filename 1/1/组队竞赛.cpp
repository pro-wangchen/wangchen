#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	int N = 0;
	while (cin >> N)
	{
		vector<int> v;
		int tmp;
		for (int i = 0; i < N * 3; i++)
		{
			cin >> tmp;
			v.push_back(tmp);
		}
		sort(v.begin(), v.end());
		
		long long sum = 0;
		for (int i = N; i < N * 3; i += 2)
		{
			sum += v[i];
		}
		
		cout << sum << endl;
	}
	return 0;

}