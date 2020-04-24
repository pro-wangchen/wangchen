class Solution {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers) {
		if (numbers.empty())
		{
			return 0;
		}
		sort(numbers.begin(), numbers.end());
		int k = numbers.size() / 2;
		int count = 0;
		for (int i = 0; i < numbers.size(); i++)
		{
			if (numbers[i] == numbers[k])
			{
				count++;
			}
		}
		if (count > k)
		{
			return numbers[k];
		}
		return 0;

	}
};