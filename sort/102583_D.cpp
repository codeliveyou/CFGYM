#include<bits/stdc++.h>

using namespace std;
mt19937 rnd(2023);

const int N = 1e3 + 10;
int a[N], ct[N], sz;
bool flag[N], g[N][N];

bool calc(int v) {
	if (flag[v]) {
		return 0;
	}
	flag[v] = 1;

	for (int to = 0; to < N; ++to) {
		if (g[v][to] && ct[to] == -1) {
			ct[to] = v;
			return 1;
		}
	}

	for (int i = 0; i < sz; ++i) {
		int to = rnd() % sz;
		if (g[v][to] && calc(ct[to])) {
			ct[to] = v;
			return 1;
		}
	}

	vector < int > per;
	for (int i = 0; i < N; ++i)
		if (g[v][i])
			per.push_back(i);
	shuffle(per.begin(), per.end(), rnd);

	for (int to: per) {
		if (calc(ct[to])) {
			ct[to] = v;
			return 1;
		}
	}
	return 0;
}

int ans[N][N];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
	}
	sz = a[n - 1];

	for (int i = 0; i + 1 < n; ++i) {
		if (a[i] * 2 > a[i + 1]) {
			puts("No");
			return 0;
		}
	}

	int p = 0;
	for (int i = 0; i < n; ++i) {
		for (int x = 0; x < a[i]; ++x) {
			for (int y = 0; y < a[i]; ++y) {
				g[x][y] = x >= p && y >= p;
			}
		}
		for (int t = 0; t < p; ++t) {
			for (int x = 0; x < N; ++x)
				ct[x] = -1;
			int cnt = 0;
			for (int x = p; x < a[i]; ++x) {
				memset(flag, 0, sizeof flag);
				cnt += calc(x);
			}
			vector < pair < int, int >> ed;
			for (int x = p; x < a[i]; ++x) {
				if (ct[x] != -1) {
					ans[ct[x]][x] = t;
					g[ct[x]][x] = 0;
				}
			}
		}
		for (int x = 0; x < a[i]; ++x) {
			for (int y = 0; y < a[i]; ++y) {
				if ((x >= p) ^ (y >= p)) {
					g[x][y] = 1;
				}
			}
		}
		for (int t = p; t < a[i]; ++t) {
			for (int x = 0; x < N; ++x)
				ct[x] = -1;
			int cnt = 0;
			for (int x = 0; x < a[i]; ++x) {
				memset(flag, 0, sizeof flag);
				cnt += calc(x);
			}
			for (int x = 0; x < a[i]; ++x) {
				if (ct[x] != -1) {
					ans[ct[x]][x] = t;
					g[ct[x]][x] = 0;
				}
			}
		}
		p = a[i];
	}

	puts("Yes");
	for (int i = 0; i < sz; ++i) {
		for (int j = 0; j < sz; ++j) {
			printf("%d%c", ans[i][j] + 1, j == sz - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
