class Gift {
public:
	int getValue(vector<int> gifts, int n) {
		sort(gifts.begin(), gifts.end());
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			if (gifts[i] == gifts[n / 2])
			{
				count++;
			}
		}
		if (count > n / 2)
		{
			return gifts[n / 2];
		}
		else return 0;

	}
};