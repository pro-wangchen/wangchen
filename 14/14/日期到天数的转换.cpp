#include <iostream>
using namespace std;


int main()
{
	int arr[13] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
	int year;
	int month;
	int day;
	while (cin >> year >> month >> day)
	{
		int sum = 0;
		sum += day;
		sum += arr[month - 1];
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			sum++;
		}
		cout << sum << endl;
	}
	return 0;
}