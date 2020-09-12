#include <iostream>
#include <vector>
using namespace std;
int N, M;
vector<vector<int>> migo;
vector<vector<int>> tmp;
vector<vector<int>> best;

void fmigo(int i, int j)
{
	migo[i][j] = 1;
	tmp.push_back({ i,j });
	if (i == N - 1 && j == M - 1)
	{
		if (best.empty() || tmp.size() < best.size())
		{
			best = tmp;
		}
	}
	if (i - 1 >= 0 && migo[i - 1][j] == 0) fmigo(i - 1, j);
	if (i + 1 < N && migo[i + 1][j] == 0) fmigo(i + 1, j);
	if (j + 1 < M && migo[i][j + 1] == 0) fmigo(i, j + 1);
	if (j - 1 >= 0 && migo[i][j - 1] == 0) fmigo(i, j - 1);
	migo[i][j] = 0;
	tmp.pop_back();
}
int main()
{
	while (cin >> N >> M)
	{
		migo = vector<vector<int>>(N, vector<int>(M, 0));
		tmp.clear();
		best.clear();
		for (auto & i : migo)
		{
			for (auto & e : i)
			{
				cin >> e;
			}
		}
		fmigo(0, 0);
		for (auto i : best)
		{
			cout << "(" << i[0] << "," << i[1] << ")" << endl;
		}
	}

	return 0;
}