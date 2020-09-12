class LCA {
public:
	int getLCA(int a, int b)
	{
		//Âú¶þ²æÊ÷
		//        1
		//      2    3
		//  4  5     6  7
		while (a != b)
		{
			if (a > b) a /= 2;
			if (a < b) b /= 2;
		}
		return a;
	}
};