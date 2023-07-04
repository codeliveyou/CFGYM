#include <bits/stdc++.h>
using namespace std;

const int N = 220000;

vector<int> V[N], Q[N];
int a[N], L[N], R[N], Z[N];
int s[N], e[N], _s[N], _e[N];
long long sum[N], ans[N];

int main() {
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i);
		V[a[i]].push_back(i);
	}
	for(int i = 1; i <= q; i ++) {
		scanf("%d %d %d", L + i, R + i, Z + i);
		Q[Z[i]].push_back(i);
	}
	int sz = 0;
	for (int i = 1; i <= m; i++) {
		int l = 0, r = 0, _sz = 0;
		for (int j = 0, k = 0; j < sz; j++) {
			while (k < sz && s[k] <= e[j]) k++;
			int L = n + 1, R = n + 1;
			if (k < sz) {
				while (j + 1 < sz && e[j + 1] < s[k]) j++;
				L = s[j], R = e[k];
			}
			while (l < V[i].size() && V[i][l] < L) l++;
			while (r < V[i].size() && V[i][r] <= R) {
				_s[_sz] = V[i][r];
				_e[_sz] = V[i][r];
				_sz++;
				r++;
			}
			if (l < V[i].size() && V[i][l] <= R) continue;
			if (L <= n) {
				_s[_sz] = L;
				_e[_sz] = R;
				_sz++;
			}
		}
		while (r < V[i].size()) {
			_s[_sz] = V[i][r];
			_e[_sz] = V[i][r];
			_sz++;
			r++;
		}
		sz = _sz;
		for (int j = 0; j < sz; j++) {
			s[j] = _s[j], e[j] = _e[j];
		}
		
		for (int j = 0; j < sz - 1; j++) {
			sum[j + 1] = sum[j] - 1LL * (s[j + 1] - s[j]) * e[j + 1];
		}
		for (int j : Q[i]) {
			int l = lower_bound(s, s + sz, L[j]) - s;
			int r = upper_bound(e, e + sz, R[j]) - e - 1;
			if (l > r) continue;
			ans[j] = sum[r] - sum[l] + (R[j] + 1) * 1LL * (s[r] - s[l]) + 1LL * (s[l] - L[j] + 1) * (R[j] + 1 - e[l]);
		}
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << endl;
	return 0;
}
