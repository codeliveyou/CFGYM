#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 10;
long long a[maxn], b[maxn];
int dp[maxn];
int main() {
	int tcase, n; cin >> tcase;
	while(tcase --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i) {
			scanf("%lld", a + i);
		}
		for(int i = 1; i <= n; ++ i) {
			scanf("%lld", b + i);
			a[i] = a[i] - b[i] + a[i - 1];
		}
		for(int i = 1; i <= n; ++ i) {
			dp[i] = -1;
			for(int j = 0; j < i; ++ j) {
				if(a[i] >= a[j] && dp[j] != -1) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}
		printf("%d\n", dp[n]);
	}
	return 0;
}
