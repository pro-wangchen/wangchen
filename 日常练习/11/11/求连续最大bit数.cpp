#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	//����������
	//��������ֿ����ַ�����������1�룬���Կ����������λ�ǲ���1,����Ǿ���count++,Ȼ������1��
	//��count��max_count��ȣ������ֵ��max_count
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