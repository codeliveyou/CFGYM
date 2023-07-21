#include <bits/stdc++.h>

#define ls ((u) << 1)
#define rs ((ls) | 1)
#define md (L + R >> 1)

using namespace std;

const int N = 2.5e5 + 10;
const int M = 1 << 19;
const int K = 1 << 18;

char a[N], s[M], flag[M];

void pushUp(int u) {
	s[u] = s[ls] ^ s[rs];
}

void pushDownSubTree(int u, int L, int R, int B) {
	flag[u] ^= B;
	if (R - L >= 7) {
		return;
	}

	for (int i = L; i <= R; ++i) {
		if (B & (1 << (i & 3))) {
			s[u] ^= 1;
		}
	}
}

void pushDown(int u, int L, int R) {
	if (L == R) {
		return;
	}
	if (!flag[u]) {
		return;
	}
	pushDownSubTree(ls, L, md, flag[u]);
	pushDownSubTree(rs, md + 1, R, flag[u]);
	flag[u] = 0;
	pushUp(u);
}

void update(int u, int L, int R, int l, int r, int B) {
	if (R < l || L > r) {
		return;
	}
	if (l <= L && R <= r) {
		pushDownSubTree(u, L, R, B);
		return;
	}
	pushDown(u, L, R);
	update(ls, L, md, l, r, B);
	update(rs, md + 1, R, l, r, B);
	pushUp(u);
}

char calcSum(int u, int L, int R, int l, int r) {
	if (R < l || L > r) {
		return 0;
	}
	if (l <= L && R <= r) {
		return s[u];
	}
	pushDown(u, L, R);
	int ans = calcSum(ls, L, md, l, r);
	ans ^= calcSum(rs, md + 1, R, l, r);
	return ans;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("inputdata.txt", "r", stdin);
	freopen("outputdata.txt", "w", stdout);
	#endif
	int n, q;
	scanf("%d%d", & n, & q);
	a[0] = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", & a[i]);
	}
	for (int it = 1; it <= 3; ++it) {
		for (int i = 1; i <= n; ++i) {
			a[i] ^= a[i - 1];
		}
	}

	for (int i = 1; i <= n; ++i) {
		s[K + i] = a[i];
	}
	for (int i = K - 1; i > 0; --i) {
		pushUp(i);
	}

	for (int i = 1; i <= q; ++i) {
		int t, L, R;
		scanf("%d%d%d", & t, & L, & R);
		if (t == 1) {
			if (R - L + 1 >= 4) {
				int nl = L + 4 * ((R - L + 1) / 4);
				update(1, 0, K - 1, L, nl - 1, (1 << (L & 3)));
				L = nl;
			}

			if (L > R) {
				continue;
			}
			int B = (1 << (L & 3)) + (1 << ((R + 1) & 3));
			update(1, 0, K - 1, L, n, B);
		} else {
			int ans = 0;
			if ((R - L + 1) & 1) {
				ans ^= calcSum(1, 0, K - 1, n, n);
				ans ^= calcSum(1, 0, K - 1, n - 1, n - 1);
			}
			ans ^= calcSum(1, 0, K - 1, R - 1, R - 1);
			if (L >= 2) {
				ans ^= calcSum(1, 0, K - 1, L - 2, L - 2);
			}
			ans ^= calcSum(1, 0, K - 1, n - L, n - L);
			if (R != n) {
				ans ^= calcSum(1, 0, K - 1, n - R - 1, n - R - 1);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
