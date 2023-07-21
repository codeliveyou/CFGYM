#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;
const int N = 1e4 + 10;
const int M = 1e2 + 10;

int dp[2][M][M], sum[N][M];

int main() {
	int n, m, p;
	scanf("%d%d%d", & n, & m, & p);
	m = min(m, p + 1);
	dp[0][0][0] = sum[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 1; k <= p; k++) {
				dp[1][j][k] = (dp[0][j - 1][k - 1] + dp[1][j - 1][k - 1]) % mod;
			}
		}
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= p; k++) {
				dp[1][j][k] = (dp[1][j][k] + sum[j][k]) % mod;
			}
		}
		for (int j = m; j >= 0; j--) {
			for (int k = 0; k <= p; k++) {
				dp[0][j][k] = dp[1][j][k];
				dp[1][j][k] = 0;
				sum[j][k] = (sum[j + 1][k] + dp[0][j][k]) % mod;
			}
		}
	}
	int ans = 0;
	for (int j = 0; j <= m; j++) {
		for (int k = 0; k <= p; k++) {
			ans = (ans + dp[0][j][k]) % mod;
		}
	}
	printf("%d\n", ans);
	return 0;
}
