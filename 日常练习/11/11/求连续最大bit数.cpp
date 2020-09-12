#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	//进行与运算
	//将这个数字看成字符串，让它和1与，可以看到它的最低位是不是1,如果是就让count++,然后右移1，
	//让count和max_count相比，把最大值给max_count
	int x;
	while (cin >> x)
	{
		int count = 0, max_count = 0;
		while (x)
		{
			if (x & 1)
			{
				count++;
				max_count = max(count, max_count);
			}
			else
			{
				count = 0;
			}
			x = x >> 1;
		}
		cout << max_count << endl;
	}

	return 0;
}