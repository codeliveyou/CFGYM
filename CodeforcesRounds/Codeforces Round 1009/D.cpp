#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int x[N];
int r[N];

int calc(long long x) {
	int a = sqrt(x);
	while(1ll * a * a < x) a ++;
	while(1ll * a * a > x) a --;
	return a;
}

int calc(int x, int st, int ed) {
	int o = (st + ed) / 2;
	int r = (ed - st) / 2;
	if(abs(o - x) >= r) return 0;
	long long y = 1ll * r * r - 1ll * (o - x) * (o - x);
	return calc(y);
}

bool bad(int x, int a, int b, int c, int d) {
	long long o1 = (a + b) / 2;
	long long o2 = (c + d) / 2;
	long long r1 = (b - a) / 2;
	long long r2 = (d - c) / 2;
	return r1 * r1 - (o1 - x) * (o1 - x) >= r2 * r2 - (o2 - x) * (o2 - x);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int T; cin >> T;
	while(T --) {
		int n, k; scanf("%d %d", &n, &k);
		for(int i = 0; i < n; i ++) scanf("%d", x + i);
		for(int i = 0; i < n; i ++) scanf("%d", r + i);
		vector<pair<int, int>> p;
		for(int i = 0; i < n; i ++) {
			p.push_back({x[i] - r[i], x[i] + r[i]});
		}
		sort(p.begin(), p.end());
		int m = n;
		n = 0;
		for(int i = 0; i < m; i ++) {
			if(n == 0) n ++;
			else if(p[n - 1].second < p[i].second) {
				while(n > 0 && p[n - 1].first >= p[i].first) n --;
				p[n ++] = p[i];
			}
		}
		long long answer = 0;
		for(int i = 0; i < n; i ++) {
			for(int j = p[i].first; j <= p[i].second; j ++) {
				if(i > 0 && p[i - 1].second >= j && bad(j, p[i - 1].first, p[i - 1].second, p[i].first, p[i].second)) continue;
				if(i + 1 < n && j >= p[i + 1].first && !bad(j, p[i].first, p[i].second, p[i + 1].first, p[i + 1].second)) continue;
				int h = calc(j, p[i].first, p[i].second);
				answer += 2 * (h + 1) - 1;
			}
		}
		cout << answer << endl;
//		exit(0);
	}
	return 0;
}