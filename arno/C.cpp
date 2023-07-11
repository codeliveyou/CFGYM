#include<bits/stdc++.h>
using namespace std;
int lbit(int x)
{
	return x & -x;
}
int main()
{
	int t; cin >> t;
	while(t --)
	{
		int n, x;
		cin >> n >> x;
		if(x < (1 << (int)(log2(n))))
		{
			puts("NO");
		}
		else
		{
			puts("YES");
			for(int i = 1; i <= n; i ++)
			{
				printf("%d ", lbit(i));
			}
			puts("");
		}
	}
	return 0;
}
