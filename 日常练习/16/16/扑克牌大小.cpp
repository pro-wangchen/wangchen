#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> split(string str, char sep) {
	stringstream ss(str);
	string temp;
	vector<string> res;
	while (getline(ss, temp, sep)) {
		res.push_back(temp);
	}
	return res;
}
int judgePoker(vector<string> poker) {
	int flag = -1;
	if (poker.size() == 1) {
		flag = 0;//����
	}
	else if (poker.size() == 2) {
		if (poker[0] == string("joker") || poker[1] == string("joker"))
			flag = 5;//����
		else
			flag = 1;//��ͨ����
	}
	else if (poker.size() == 3)
		flag = 2;//����
	else if (poker.size() == 4)
		flag = 3;//ը��
	else if (poker.size() == 5)
		flag = 4;//˳��
	return flag;
}

int main() {
	string str;
	vector<string> table = { "3","4","5","6","7","8","9","10",
						  "J","Q","K","A","2","joker","JOKER" };
	while (getline(cin, str)) {
		int win = -1;//0��ʾ���ܱȣ�1��ʾ��һ����2��ʾ�ڶ���
		vector<string> vec = split(str, '-');
		vector<string> poker1 = split(vec[0], ' ');
		vector<string> poker2 = split(vec[1], ' ');
		int flag1 = -1, flag2 = -1;
		flag1 = judgePoker(poker1);
		flag2 = judgePoker(poker2);
		if (flag1 == 5 || flag2 == 5 || flag1 == 3 || flag2 == 3) {
			if (flag1 == 5)//һ���ж���
				win = 1;
			else if (flag2 == 5)
				win = 2;
			else if (flag1 == flag2 && flag1 == 3) {//����ը��
				auto it1 = find(table.begin(), table.end(), poker1[0]);
				auto it2 = find(table.begin(), table.end(), poker2[0]);
				if (it1 < it2)
					win = 2;
				else
					win = 1;
			}
			else if (flag1 == 3 && flag2 != 3)//ֻ��һ����ը��
				win = 1;
			else if (flag1 != 3 && flag2 == 3)
				win = 2;
		}
		else if (flag1 == flag2) {
			auto it1 = find(table.begin(), table.end(), poker1[0]);
			auto it2 = find(table.begin(), table.end(), poker2[0]);
			if (it1 < it2)
				win = 2;
			else
				win = 1;
		}
		else
			win = 0;
		if (!win)
			cout << "ERROR" << endl;
		else if (win == 1) {
			int i = 0;
			for (; i < poker1.size() - 1; i++)
				cout << poker1[i] << " ";
			cout << poker1[i] << endl;
		}
		else if (win == 2) {
			int i = 0;
			for (; i < poker2.size() - 1; i++)
				cout << poker2[i] << " ";
			cout << poker2[i] << endl;
		}
	}
	return 0;
}