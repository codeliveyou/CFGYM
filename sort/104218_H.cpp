#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int mod = 1e9 + 7;
const int N = 1e6 + 10;

int dp[N], sum_dp[N];

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	k --;
	for(int i = 0; i <= n; i ++) {
		dp[i] = (sum_dp[i] - sum_dp[max(0, i - k - 1)] + mod) % mod;
		if(i <= k) {
			dp[i] = (dp[i] + 1) % mod;
		}
		sum_dp[i + 1] = (sum_dp[i] + dp[i]) % mod;
	}
	printf("%d\n", dp[n]);
	return 0;
}
