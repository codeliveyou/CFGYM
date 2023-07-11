#include "bits/stdc++.h"

using namespace std;
const int N = 2e5 + 10;
pair<int, long long> par[N];
int tim[N];
int solve() {
	int n, m, h;
	cin >> n >> m >> h;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m; j ++) {
			scanf("%d", tim + j);
		}
		sort(tim, tim + m);
		long long tmp = 0;
		par[i] = {0, 0};
		for(int j = 0; j < m; j ++) {
			tmp += tim[j];
			if(tmp > h) {
				break;
			}
			par[i].first --;
			par[i].second += tmp;
		}
	}
	int x = par[0].first;
	long long y = par[0].second;
	sort(par, par + n);
	for(int i = 0; i < n; i ++) {
		if(par[i].first == x && par[i].second == y) {
			return i + 1;
		}
	}
}

int main() {
	int T; cin >> T;
	while(T --) {
		cout << solve() << endl;
	}
	return 0;
}
