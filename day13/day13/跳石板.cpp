//小易来到了一条石板路前，每块石板上从1挨着编号为：1、2、3.......
//这条石板路要根据特殊的规则才能前进：对于小易当前所在的编号为K的 石板，
//小易单次只能往前跳K的一个约数(不含1和K)步，即跳到K + X(X为K的一个非1和本身的约数)的位置。
//小易当前处在编号为N的石板，他想跳到编号恰好为M的石板去，小易想知道最少需要跳跃几次可以到达。
//例如：
//N = 4，M = 24：
//4->6->8->12->18->24
//于是小易最少需要跳跃5次，就可以从4号石板跳到24号石板
#include <iostream>

using namespace std;
int bigfactor(int n)
{
	int tmp = 0;
	for (int i = 1; i <= n/2+1 ; i++)
	{
		
		if ((n%i) == 0 && i > tmp)
		{
			tmp = i;
		}
	}
	return tmp;
}
int main()
{
	//使用贪心算法的思路，每一步都取最大的约数，如果最后一步超过了这个数字，那么就看看看前一步
	//到这个数的距离是不是约数，是就步数+1，返回步数，不是就返回-1
	int m, n;
	int count = 0;
	
	cin >> n >> m;
	
		while (n < m)
		{
			n += bigfactor(n);
			count++;			
		}	
		if (n % (n - m) == 0)
		{
				cout << count << endl;
				
		}
		else
		{
				cout << -1 << endl;
				
		}
		
	

	return 0;
}