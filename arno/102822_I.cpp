#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve(int tcase) {
	LL n, c, Q;
	cin >> n >> c >> Q;
	LL p = 1;
	while(p * (p + 1) < c) {
		p ++;
	}
	LL BF = p * (p + 3);
	vector<LL> dp(BF, LL(1e12));
	dp[0] = 0;
	for(LL i = 1; i < 2 * p + 3; i ++) {
		if(dp[i] < i * i + c) continue;
		for(LL j = i; j < BF; j ++) {
			dp[j] = min(dp[j], dp[j - i] + i * i + c);
		}
	}
	vector<LL> h(n);
	for(LL& x : h) cin >> x;
	vector<LL> queries(Q);
	for(LL& x : queries) cin >> x;
	vector<int> id(Q);
	
	iota(id.begin(), id.end(), 0);
	sort(id.begin(), id.end(), [&](int a, int b) {
		return queries[a] < queries[b];
	});
	
	vector<LL> ans(Q, -1);

	sort(h.begin(), h.end());
	int hidx = 0;
	vector<LL> s0(p, 0), s1(p, 0);
	for(int i : id){
		while(hidx < (int)h.size() && h[hidx] <= queries[i] - BF){
			s0[h[hidx] % p] += 1;
			s1[h[hidx] % p] += h[hidx];
			hidx++;
		}
		LL res = 0;
		for(int idx = hidx; idx < (int)h.size() && h[idx] < queries[i]; idx++){
			res += dp[queries[i] - h[idx]];
		}
		LL ref = BF / p * p - p + (queries[i] % p);
		LL res1 = 0, res2 = 0;
		for(LL r = 0; r < p; r++){
			res1 += dp[ref] * s0[r];
			res2 += ((queries[i] - ref) * s0[r] - s1[r]);
			ref--;
		}
		res += res1 + res2 / p * (p*p+c);
		ans[i] = res;
	}
	printf("Case #%d:\n", tcase);
	for(int i = 0; i < ans.size(); i ++) {
		printf("%I64d\n", ans[i]);
	}
}

int main(){
	int T; cin >> T;
	for(int tcase = 1; tcase <= T; tcase ++) {
		solve(tcase);
	}
	return 0;
}
