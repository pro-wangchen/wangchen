//�������������������
//
//xcopy / s c : \ d : \��
//
//�����������£�
//
//����1��������xcopy
//
//����2���ַ��� / s
//
//����3���ַ���c : \
//
//	����4 : �ַ���d : \
//
//	���дһ��������������ʵ�ֽ������и�����������������
//
//
//
//	��������
//
//	1.�����ָ���Ϊ�ո�
//	2.�����á������������Ĳ���������м��пո񣬲��ܽ���Ϊ���������
//	  ����������������xcopy / s ��C : \program files�� ��d : \��ʱ��������Ȼ��4����
//	  ��3������Ӧ�����ַ���C : \program files��������C : \program��ע���������ʱ��
//	  ��Ҫ������ȥ�������Ų�����Ƕ�������
//	3.����������
//	4.������������֤��������ֲ�����Ҫ�������
#include <iostream> 
#include <string>
#include <vector>
using namespace std;

int main1()
{
	string s;
	while (getline(cin,s))
	{
		vector<string> v;
		string tmp = "";
		for (int i = 0; i < s.size(); i++)
		{
			int flag = -1;
			if (s[i] == '"')
			{
				flag *= -1;
			}
			if (s[i] == ' ' && flag == -1)
			{
				v.push_back(tmp);
				tmp = "";
			}
			else
			{
				tmp += s[i];
			}
		}
		v.push_back(tmp);
		cout << v.size() << endl;
		for (auto &i : v)
		{
			cout << i << endl;
		}
	}
	return 0;
}