#include <bits/stdc++.h>
#define ls (u << 1)
#define rs (ls | 1)
#define md (L + R >> 1)

using namespace std;
const int N = 1e5 + 10;
pair<int, int> star[N];
vector<int> seg[N << 2];

void build(int u, int L, int R) {
	if (L == R) {
		seg[u].push_back(star[L].second);
	}
	else {
		build(ls, L, md);
		build(rs, md + 1, R);
		seg[u].resize(seg[2 * u].size() + seg[2 * u + 1].size());
		merge(seg[ls].begin(), seg[ls].end(), seg[rs].begin(), seg[rs].end(), seg[u].begin());
	}
}

int calc(int l, int r, int x, int y, int u, int L, int R) {
	if(r < l) {
		return 0;
	}
	if (l <= L && R <= r) {
		int UP = upper_bound(seg[u].begin(), seg[u].end(), y) - seg[u].begin();
		int DN = lower_bound(seg[u].begin(), seg[u].end(), x) - seg[u].begin();
		return UP - DN;
	}
	if (l > R || L > r) {
		return 0;
	}
	int ans = calc(l, r, x, y, ls, L, md);
	ans += calc(l, r, x, y, rs, md + 1, R);
	return ans;
}


int main() {
#ifdef ONLINE_JUDGE
	freopen("stars.in", "r", stdin);
	freopen("stars.out", "w", stdout);
#endif
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i ++) {
		scanf("%d %d", &star[i].first, &star[i].second);
	}
	sort(star, star + n);
	build(1, 0, n - 1);
	while (m --) {
		int x1, x2, y1, y2;
		scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
		int L = lower_bound(star, star + n, make_pair(x1, INT_MIN)) - star;
		int R = lower_bound(star, star + n, make_pair(x2 + 1, INT_MIN)) - star - 1;
		printf("%d\n", calc(L, R, y1, y2, 1, 0, n - 1));
	}
	return 0;
}
