#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;

int a[maxn], b[maxn], pr[maxn], nx[maxn];

void solve() 
{
	int n; scanf("%d", &n);
	bool F = true;
	for (int i = 1; i <= n; i++) 
	{
		scanf("%d", b + i);
		if (b[i] < i) 
		{
			F = false;
		}
	}
	if (b[1] > n or !F) 
	{
		puts("-1");
		return;
	}
	for (int i = 1; i <= n; i++) 
	{
		if(b[i] != i) 
		{
			F = false;
		}
	}
	if (F) 
	{
		for (int i = 1; i <= n; i++) 
		{
			printf("%d%c", 0, " \n"[i == n]);
		}
		return;
	}
	F = 1;
	for (int i = 1; i <= n; i++) 
	{
		F &= b[i] > i;
	}
	if (!F) 
	{
		puts("-1");
		return;
	}
	int col = INT_MAX;
	for (int i = 1; i <= n; i++) 
	{
		col = min(col, (b[i] > n ? 2 * n : b[i]) - i + 1);
	}
	fill(pr + 1, pr + n + 1, 0);
	fill(nx + 1, nx + n + 1, 0);
	int tot = 0;
	bool good = 1;
	for (int i = 1, j = col; i < n; i++) 
	{
		if (!pr[i]) tot++;
		if (tot > col) 
		{
			good = 0;
			break;
		}
		if (b[i] < b[i + 1]) 
		{
			nx[i] = b[i + 1], pr[b[i + 1]] = i;
		} else 
		{
			while (j <= n and (pr[j] or j == b[1])) j++;
			nx[i] = j, pr[j] = i;
		}
	}
	if (!good) 
	{
		puts("-1");
		return;
	}
	tot = 0;
	for (int i = 1; i <= n; i++) 
	{
		printf("%d%c", a[i] = pr[i] ? a[pr[i]] : ++tot, " \n"[i == n]);
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) 
	{
		solve();
	}
	return 0;
}
