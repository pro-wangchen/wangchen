class Parenthesis {
public:
	bool chkParenthesis(string A, int n)
	{
		stack<char> s;
		for (int i = 0; i < n; i++)
		{
			if (A[i] == '(')
			{
				s.push(A[i]);
			}
			else if (A[i] == ')')
			{
				if (s.empty())
				{
					return false;
				}
				s.pop();
			}
			else
			{
				return false;
			}
		}
		if (s.empty())
		{
			return true;
		}
		else return false;
	}
};