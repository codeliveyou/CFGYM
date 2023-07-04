#include <bits/stdc++.h>
using namespace std;
template<typename T> struct hungarian {
	int n;
	vector<vector<T>> a;
	vector<T> u, v;
	vector<int> p, way;
	T inf;
	hungarian(int n_) : n(n_), u(n+1), v(n+1), p(n+1), way(n+1) {
		a = vector<vector<T>>(n, vector<T>(n));
		inf = numeric_limits<T>::max();
	}
	pair<T, vector<int>> assignment() {
		for (int i = 1; i <= n; i++) {
			p[0] = i;
			int j0 = 0;
			vector<T> minv(n+1, inf);
			vector<int> used(n+1, 0);
			do {
				used[j0] = true;
				int i0 = p[j0], j1 = -1;
				T delta = inf;
				for (int j = 1; j <= n; j++) if (!used[j]) {
					T cur = a[i0-1][j-1] - u[i0] - v[j];
					if (cur < minv[j]) minv[j] = cur, way[j] = j0;
					if (minv[j] < delta) delta = minv[j], j1 = j;
				}
				for (int j = 0; j <= n; j++)
					if (used[j]) u[p[j]] += delta, v[j] -= delta;
					else minv[j] -= delta;
				j0 = j1;
			} while (p[j0] != 0);
			do {
				int j1 = way[j0];
				p[j0] = p[j1];
				j0 = j1;
			} while (j0);
		}
		vector<int> ans(n);
		for (int j = 1; j <= n; j++) ans[p[j]-1] = j-1;
		return make_pair(-v[0], ans);
	}
};

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	hungarian<int> HGR0(n), HGR1(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			HGR0.a[i][j] = (n + 10) * (n + 10);
			HGR1.a[i][j] = (n + 10) * (n + 10);
		}
	}

	map<pair<int, int>, int> mp;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		a --, b --;
		mp[{a, b}] = c;
		if (c == 0) {
			HGR0.a[a][b] = -(n + 10);
			HGR1.a[a][b] = -1;
		}
		else {
			HGR1.a[a][b] = -(n + 10);
			HGR0.a[a][b] = -1;
		}
	}

	int v0, v1;
	vector<int> M0, M1;
	tie(v0, M0) = HGR0.assignment();
	tie(v1, M1) = HGR1.assignment();

	int out0 = 0, out1 = 0;
	for (int i = 0; i < n; i++) {
		int j = M0[i];
		if (HGR0.a[i][j] == (n + 10) * (n + 10)) {
			M0[i] = -1;
			out0++;
		}
		j = M1[i];
		if (HGR1.a[i][j] == (n + 10) * (n + 10)) {
			M1[i] = -1;
			out1++;
		}
	}
	
	vector<int> ans = M0;
	int tot = 0;
	for (int i = 0; i < n; i++) {
		if (M0[i] != -1) {
			tot += mp[{i, M0[i]}];
		}
	}
	
	vector<vector<int>> g(2*n);
	
	for (int i = 0; i < n; i++) {
		if (M0[i] != M1[i]) {
			if (M0[i] != -1) {
				int j = n + M0[i];
				g[i].push_back(j), g[j].push_back(i);
			}
			if (M1[i] != -1) {
				int j = n + M1[i];
				g[i].push_back(j), g[j].push_back(i);
			}
		}
	}
	
	auto ins = [&](int i, int j) {
		if (i > j) swap(i, j);
		return M1[i] == j - n;
	};
	
	vector<int> flag(2*n);
	for (int T = 0; T < 2; T++) {
		auto cond = [&](int i) {
			if (T == 0) {
				return g[i].size() == 1 and ins(i, g[i][0]);
			}
			else {
				return !flag[i] and g[i].size() == 2;
			}
		};
		for (int i = 0; i < 2*n; i++) {
			if (cond(i)) {
				if (tot == k) break;
				vector<int> v;
				int prev = -1, at = i;
				if (T == 1) {
					for (int j : g[at]) {
						if (!ins(at, j)) {
							prev = j;
						}
					}
				}
				while (!flag[at]) {
					flag[at] = 1;
					if (at < n) {
						v.push_back(at);
					}
					for (int j : g[at]) {
						if (j != prev) {
							prev = at, at = j;
							break;
						}
					}
				}
				for (int j = 0; j < v.size() and tot <= k; j++) {
					int a = v[j];
					tot += mp[{a, M1[a]}] - mp[{a, M0[a]}];
					ans[a] = M1[a];
					if (tot > k) {
						tot -= mp[{a, ans[a]}], ans[a] = -1;
						break;
					}
				}
			}
		}
	}
	
	int E = 0;
	for (int i : ans) {
		if (i != -1) {
			E++;
		}
	}
	printf("%d\n", E);
	for (int i = 0; i < n; i++) {
		if (ans[i] != -1) {
			printf("%d %d\n", i + 1, ans[i] + 1);
		}
	}
	return 0;
}
