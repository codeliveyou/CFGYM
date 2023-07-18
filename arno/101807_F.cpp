#include <bits/stdc++.h>
using namespace std;

const int N = 5050;

int p[N], s[N], c[N], a[N], b[N];

int main()
{
	int n;
	cin >> n;
	for(int i = 0; i < n / 2; i ++)
	{
		scanf("%d %d", a + i, b + i);
	}
	
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d %d %d", p + i, s + i, c + i);
	}
	
	for(int i = 0; i < n / 2; i ++)
	{
		if(p[a[i]] < p[b[i]])
		{
			swap(a[i], b[i]);
		}
	}
	
	for(int i = 1; i <= n; i ++)
	{
		int mn = 1, mx = n;
		for(int j = 0; j < n / 2; j ++)
		{
			if(p[b[j]] > p[i] + 3)
			{
				mn += 2;
			}
			
			else if(p[a[j]] > p[i] + 3)
			{
				mn += 1;
			}
			
			else if(p[b[j]] + 3 > p[i] + 3 && p[a[j]] == p[i] + 3)
			{
				if(b[j] != i && a[j] != i)
				{
					mn += 1;
				}
			}
			
			if(p[a[j]] < p[i])
			{
				if(p[a[j]] + 3 < p[i])
				{
					mx -= 2;
				}
				else if(p[b[j]] < p[i] - 1)
				{
					mx --;
				}
			}
			
			else if(p[b[j]] + 3 < p[i])
			{
				mx --;
			}
		}
		
		printf("%d %d\n", mn, mx);
	}
	return 0;
}
