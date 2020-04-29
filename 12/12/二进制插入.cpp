/*class BinInsert {
public:
	int binInsert(int n, int m, int j, int i)
	{
		//1024=100 0000 0000‬
		//126 =000 0111 1110
		//因为题目中已经保证了n的第j到第i位均为零，所以插入进去就是左移j位后，进行或运算
		m <<= j;
		return n | m;

	}
};
*/