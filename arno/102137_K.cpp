#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int, int> pii;

const int N = 1 << 18;

struct seg {
	int l, r;
	vector<int> a;
	seg(int l = 0, int r = 0, vector<int> a = vector<int>()) : l(l), r(r), a() {}
};

seg s[2 * N + 5];

void build() {
	for (int i = 0; i < N; i++) {
		s[N + i] = seg(i, i + 1);
	}
	for (int i = N - 1; i > 0; i--) {
		s[i] = seg(s[2 * i].l, s[2 * i + 1].r);
	}
}

void insert(int x, int y) {
	x += N;
	while(x >= 1) {
		s[x].a.push_back(y);
		x >>= 1;
	}
}

void calc(int u, int l, int r, int x, int y, pii &p) {
	if (l <= s[u].l && s[u].r <= r) {
		int pos = lower_bound(s[u].a.begin(), s[u].a.end(), x) - s[u].a.begin();
		if (pos < (int)s[u].a.size() && s[u].a[pos] < y) {
			p.x = min(p.x, s[u].a[pos]);
		}
		pos = lower_bound(s[u].a.begin(), s[u].a.end(), y) - s[u].a.begin() - 1;
		if (pos >= 0 && s[u].a[pos] >= x) {
			p.y = max(p.y, s[u].a[pos]);
		}
		return;
	}
	if (l >= s[u].r || s[u].l >= r) return;
	calc(2 * u, l, r, x, y, p);
	calc(2 * u + 1, l, r, x, y, p);
}

const int M = 2e5 + 10;

int n, m;
int wolf[M][4], sheep[M][2], ans[M][4];
int X[M], XN, Y[M], YN;

void solve() {
	build();
	for (int i = 0; i < m; i++) {
		insert(sheep[i][0], sheep[i][1]);
	}
	for (int u = 1; u < 2 * N; u++) {
		sort(s[u].a.begin(), s[u].a.end());
	}
	for (int i = 0; i < n; i++) {
		pii p = {M, -1};
		calc(1, wolf[i][0], wolf[i][1], wolf[i][2], wolf[i][3], p);
		ans[i][0] = p.x;
		ans[i][1] = p.y;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			scanf("%d", wolf[i] + j);
		}
		swap(wolf[i][1], wolf[i][2]);
		wolf[i][1] ++;
		wolf[i][3] ++;
	}
	
	for (int i = 0; i < m; i++) {
		scanf("%d%d", sheep[i], sheep[i] + 1);
		X[XN ++] = sheep[i][0];
		Y[YN ++] = sheep[i][1];
	}
	
	sort(X, X + XN);
	XN = unique(X, X + XN) - X;
	sort(Y, Y + YN);
	YN = unique(Y, Y + YN) - Y;
	
	for (int i = 0; i < n; i++) {
		wolf[i][0] = lower_bound(X, X + XN, wolf[i][0]) - X;
		wolf[i][1] = lower_bound(X, X + XN, wolf[i][1]) - X;
		wolf[i][2] = lower_bound(Y, Y + YN, wolf[i][2]) - Y;
		wolf[i][3] = lower_bound(Y, Y + YN, wolf[i][3]) - Y;
	}
	
	for (int i = 0; i < m; i++) {
		sheep[i][0] = lower_bound(X, X + XN, sheep[i][0]) - X;
		sheep[i][1] = lower_bound(Y, Y + YN, sheep[i][1]) - Y;
	}
	
	solve();
	
	for (int i = 0; i < n; i++) {
		swap(wolf[i][0], wolf[i][2]);
		swap(wolf[i][1], wolf[i][3]);
		swap(ans[i][0], ans[i][2]);
		swap(ans[i][1], ans[i][3]);
	}
	
	for (int i = 0; i < m; i++) {
		swap(sheep[i][0], sheep[i][1]);
	}
	
	solve();
	
	set<vector<int>> st;
	for (int i = 0; i < n; i++) {
		vector<int> vec;
		vec.resize(4);
		for (int j = 0; j < 4; j++) {
			vec[j] = ans[i][j];
		}
		st.insert(vec);
	}
	
	cout << st.size() << endl;

	return 0;
}
