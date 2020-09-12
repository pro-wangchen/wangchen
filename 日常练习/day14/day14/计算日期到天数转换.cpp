/*
根据输入的日期，计算是这一年的第几天。。

详细描述：

输入某年某月某日，判断这一天是这一年的第几天？。

接口设计及说明：

 
 Description   : 数据转换
 Input Param   : year 输入年份
				Month 输入月份
				Day 输入天

 Output Param  :
 Return Value  : 成功返回0，失败返回-1（如：数据错误）
 
public static int iConverDateToDay(int year, int month, int day)
{
	 在这里实现功能，将结果填入输入数组中
	return 0;
}


Description   :
Input Param   :

Output Param  :
Return Value  : 成功:返回outDay输出计算后的第几天;
										  失败:返回-1

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