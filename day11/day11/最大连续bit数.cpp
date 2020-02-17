//功能 : 求一个byte数字对应的二进制数字中1的最大连续数，例如3的二进制为00000011，最大连续2个1
//
//	输入 : 一个byte型的数字
//
//	输出 : 无
//
//	返回 : 对应的二进制数字中1的最大连续数
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	//进行与运算
	//将这个数字看成字符串，让它和1与，可以看到它的最低位是不是1,如果是就让count++,然后右移1，
	//让count和max_count相比，把最大值给max_count
	int x ;
	while (cin>>x)
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



//别人的牛叉的代码，
/*
int main()
{
	int byte;
	while (cin >> byte)
	{
		int k = 0;
		for (k = 0; byte != 0; k++)
		{
			byte = byte & (byte << 1);
		}
		cout << k << endl;
	}
	return 0;
}
*/