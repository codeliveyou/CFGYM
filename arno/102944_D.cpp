#include <bits/stdc++.h>
using namespace std;

const int BN = 22, maxM = 44;
int dp[1 << BN], u[maxM], v[maxM];

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++)
	{
		cin >> u[i] >> v[i];
		u[i]--, v[i]--;
	}
	memset(dp, 0x7f, sizeof dp);
	dp[1] = 0;
	for (int i = 1; i < (1 << n); i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (((i >> v[j]) & 1) && ((i >> u[j]) & 1) == 0)
			{
				dp[i | (1 << u[j])] = min(dp[i | (1 << u[j])], dp[i] + 1);
			}
		}
	}
	int ans = 0x7f7f7f7f;
	for (int i = 1; i < (1 << n); i++)
	{
		if ((i & ((1 << k + 2) - 1)) == (1 << k + 2) - 1)
		{
			ans = min(ans, dp[i]);
		}
	}
	cout << ans << '\n';
	return 0;
}
