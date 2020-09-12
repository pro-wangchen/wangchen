#include <iostream>

using namespace std;
int num(int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}
	return num(n - 1) + num(n - 2);
}
int main()
{
	int n;
	while (cin >> n)
	{
		cout << num(n) << endl;
	}

	return 0;
}



#include <iostream>
using namespace std;
int main() {
	int month;
	while (cin >> month) {
		int first = 1;
		int second = 1;
		int result;
		for (int i = 3; i <= month; ++i) {
			result = first + second;
			first = second;
			second = result;
		} 
		cout << result << endl;
	} 
	return 0;
}
