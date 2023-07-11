#include<bits/stdc++.h>

using namespace std;
using LL = long long;
const LL inf = 1e18;

const int N = 1e3 + 10;
int a[N], b[N];
LL dp[N][N];

int main(){
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i ++) {
		scanf("%d", a + i);
	}
	for(int i = 0; i < k; i ++) {
		scanf("%d", b + i);
	}
	for(int i = 0; i <= n; i ++) {
		for(int j = 0; j <= k; j ++) {
			dp[i][j] = -inf;
		}
	}
	dp[0][0] = 0;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < k; j ++) {
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
			dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + (LL) a[i] * b[j]);
		}
		dp[i + 1][k] = max(dp[i + 1][k], dp[i][k]);
	}
	printf("%I64d\n", dp[n][k]);
	return 0;
}
