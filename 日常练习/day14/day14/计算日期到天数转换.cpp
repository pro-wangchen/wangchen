/*
������������ڣ���������һ��ĵڼ��졣��

��ϸ������

����ĳ��ĳ��ĳ�գ��ж���һ������һ��ĵڼ��죿��

�ӿ���Ƽ�˵����

 
 Description   : ����ת��
 Input Param   : year �������
				Month �����·�
				Day ������

 Output Param  :
 Return Value  : �ɹ�����0��ʧ�ܷ���-1���磺���ݴ���
 
public static int iConverDateToDay(int year, int month, int day)
{
	 ������ʵ�ֹ��ܣ��������������������
	return 0;
}


Description   :
Input Param   :

Output Param  :
Return Value  : �ɹ�:����outDay��������ĵڼ���;
										  ʧ��:����-1

public static int getOutDay()
{
	return 0;
}

*/
#include <iostream>
using namespace std;
int dateday(int year, int month, int day)
{
	if (year < 0 || month <= 0 || month>12 || day <= 0 || day > 31)
	{
		return -1;
	}
	int ry[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int nry[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	bool flag;
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		flag = true;
	}
	else 
		flag = false;
	if (flag)
	{
		if (day > ry[month - 1]) return -1;
	}
	else
	{
		if (day > nry[month - 1]) return -1;
	}
	int tmp = 0;
	for (int i = 0; i < month - 1; i++)
	{
		if (flag)
		{
			tmp += ry[i];
		}
		else
		{
			tmp += nry[i];
		}
	}
	return tmp+day;
}
int main1()
{
	int year, month, day;
	while (cin >> year >> month >> day)
	{
		cout << dateday(year, month, day) << endl;
	}
	
	return 0;
}