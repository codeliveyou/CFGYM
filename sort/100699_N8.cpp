#include <bits/stdc++.h>

using namespace std;
const int N = 1111;

vector < int > dp[N];
int deck[N];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("inputdata-100699N8_1.txt", "r", stdin);
	freopen("outputdata-100699N8_1.txt", "w", stdout);
	#endif
	
	int n;
	scanf("%d", & n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", deck + i);
	}
	dp[n - 1].push_back(max(deck[n], deck[n - 1]));
	vector < int > dp1, dp2;
	for (int i = n - 2; i >= 1; i--) {
		dp1 = dp[i + 2];
		dp1.push_back(max(deck[i], deck[i + 1]));
		sort(dp1.begin(), dp1.end());
		reverse(dp1.begin(), dp1.end());

		dp2 = dp[i + 3];
		dp2.push_back(max(deck[i], max(deck[i + 1], deck[i + 2])));
		sort(dp2.begin(), dp2.end());
		reverse(dp2.begin(), dp2.end());

		dp[i] = max(dp1, dp2);
	}
	for (int i = 0; i < dp[1].size(); i++) {
		printf("%d\n", dp[1][i]);
	}
	return 0;
}
