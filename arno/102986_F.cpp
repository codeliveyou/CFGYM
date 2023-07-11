#include<bits/stdc++.h>
#define x first
#define y second

using namespace std;
using LD = long double;

const int max_n = 1e5 + 10;

int n, k;
pair<LD, LD> a[max_n];

int main(){
	scanf("%d %d", &n, &k);
	k ++;
	for(int i = 0; i < n; i ++)
	{
		scanf("%Lf", &a[i].x);
	}
	for(int i = 0; i < n; i ++)
	{
		scanf("%Lf", &a[i].y);
	}
	sort(a, a + n);
	int l = 0;
	LD ans = 0, pre_max = 0, prob = 0;
	while(k --)
	{
		pre_max = ans;
		ans = 0;
		for(int i = l; i < n; i ++)
		{
			if(a[i].x < pre_max)
			{
				l ++;
				prob += a[i].y;
			}
			else
			{
				ans += a[i].x * a[i].y;
			}
		}
		ans += prob * pre_max;
	}
	printf("%Lf\n", ans);
	return 0;
}
