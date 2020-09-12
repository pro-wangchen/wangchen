#include <iostream>
#include <vector>
using namespace std;
class Board {
public:
	bool checkWon(vector<vector<int> > board)
	{
		//(00)(01)(02)
		//(10)(11)(12)
		//(20)(21)(22)
		//两个斜线
		if (board[0][0] + board[1][1] + board[2][2] == 3)return true;
		if (board[0][2] + board[1][1] + board[2][0] == 3)return true;
		//三个横线
		if (board[0][0] + board[0][1] + board[0][2] == 3)return true;
		if (board[1][0] + board[1][1] + board[1][2] == 3)return true;
		if (board[2][0] + board[2][1] + board[2][2] == 3)return true;
		//三个竖线
		if (board[0][0] + board[1][0] + board[2][0] == 3)return true;
		if (board[0][1] + board[1][1] + board[2][1] == 3)return true;
		if (board[0][2] + board[1][2] + board[2][2] == 3)return true;
		return false;
	}
};
