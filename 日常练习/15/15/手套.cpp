class Gloves {
public:
	int findMinimum(int n, vector<int> left, vector<int> right) {
		int sum = 0;
		int leftsum = 0, rightsum = 0;
		int minleft = 26, minright = 26;
		for (int i = 0; i < n; i++)
		{
			if (left[i] * right[i] == 0)
			{
				sum += (left[i] + right[i]);
			}
			else
			{
				leftsum += left[i];
				rightsum += right[i];
				minleft = min(minleft, left[i]);
				minright = min(minright, right[i]);
			}
		}
		return sum + min(leftsum - minleft+1, rightsum - minright+1) + 1;
	}
};