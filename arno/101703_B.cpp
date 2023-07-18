#include <bits/stdc++.h>

using namespace std;
using UINT = unsigned long long;

int n, x;

UINT rd() {
	UINT ans = 0;
	for(int i = 0, d; i < x; i ++) {
		if(i == 0) {
			scanf("%d", &d);
		}
		else {
			scanf(".%d", &d);
		}
		ans = ans * 256 + d;
	}
	return ans;
}

int main() {
	cin >> n >> x;
	unordered_set<UINT> st;
	for (int i = 0; i < n; i++) {
		st.insert(rd());
	}
	UINT S = rd();
	UINT T = rd();
	int in_count = 0;
	for (auto v : st) {
		if (S <= v && v <= T) {
			in_count++;
		}
	}
	UINT B = T - S - in_count - 1;
	for(; S < T; S ++) {
		if(st.count(S)) {
			continue;
		}
		if(st.count(S + 1)) {
			continue;
		}
		cout << B << endl;
		return 0;
	}
	puts("-1");
	return 0;
}

//20 4
//86.111.162.35
//135.243.207.148
//171.238.106.249
//252.241.122.161
//207.92.150.31
//185.10.59.60
//222.209.145.219
//76.31.193.137
//56.77.74.153
//201.121.107.122
//249.50.190.228
//103.119.167.73
//38.151.89.42
//104.120.178.124
//73.246.97.230
//20.41.114.253
//213.145.49.238
//69.58.67.114
//142.36.21.72
//48.83.215.79
//14.232.84.31
//169.163.253.217

