#include "bits/stdc++.h"

using namespace std;
using LL = long long;
using PQ = priority_queue<pair<LL,int>,vector<pair<LL,int>>,greater<pair<LL,int>>>;

const int N = 2e5 + 10;
LL t[N], a[N], dp[N];

LL solve(int n) {
	int m = 0;
	for(int i = 1, tx, ax; i <= n ; i ++) {
		for(scanf("%d %d", &tx, &ax); m > 0 && a[m] <= ax; m --);
		t[++ m] = tx;
		a[m] = ax;
	}
	PQ pq;
	for(int i = 1, b = 0; i <= m ; i ++) {
		while(b < i - 1 && dp[b + 1] <= t[i]) b ++;
		while(!pq.empty() && pq.top().second <= b) pq.pop();
		dp[i] = t[i] + a[b + 1] * 2;
		if(!pq.empty()) {
			dp[i] = min(dp[i], pq.top().first);
		}
		pq.push({dp[i] + 2 * a[i + 1], i});
	}
	return dp[m];
}
int main() {
	for(int n; ~scanf("%d", &n); ) {
		printf("%I64d\n", solve(n));
	}
	return 0;
}
