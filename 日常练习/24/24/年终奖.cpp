class Bonus {
public:
	int getMost(vector<vector<int> > board)
	{
		int len = board.size();
		int high = board[0].size();
		vector<vector<int>> arr(len, vector<int>(high, 0));
		arr[0][0] = board[0][0];
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < high; j++)
			{
				if (i == 0 && j == 0)
				{
					continue;
				}
				else if (i == 0)
				{
					arr[i][j] = arr[i][j - 1] + board[i][j];
				}
				else if (j == 0)
				{
					arr[i][j] = arr[i - 1][j] + board[i][j];
				}
				else
				{
					arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]) + board[i][j];
				}
			}
		}
		return arr[len - 1][high - 1];
	}
};