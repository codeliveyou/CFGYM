#include<bits/stdc++.h>
#define ls (u << 1)
#define rs (ls | 1)
using namespace std;

const int N = 1e5 + 10;
int a[N], n, m;
int mn[N * 4], pre_mn[N * 4], sub[N * 4], buf[N], ans;

void up(int u) {
	mn[u] = min(mn[ls], mn[rs]);
	if (mn[u] == mn[ls]) {
		pre_mn[u] = pre_mn[ls];
	} else {
		pre_mn[u] = pre_mn[rs];
	}
	if (a[u]) {
		if (mn[u] > 0) {
			mn[u] = 0;
			pre_mn[u] = u;
		}
	}
	mn[u] += sub[u];
}

void update(int u) {
	if (!u) {
		return;
	}
	up(u);
	update(u / 2);
}

void upgrade(int u, int x) {
	mn[u] = mn[u] - sub[u] + x;
	sub[u] = x;
	update(u);
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("mole.in", "r", stdin);
	freopen("mole.out", "w", stdout);
	#endif
	scanf("%d %d", & n, & m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		pre_mn[i] = i;
	}
	memset(mn, 0x7f, sizeof(mn));
	for (int i = 1; i <= n; i++) {
		upgrade(i, 1);
	}
	while (m--) {
		int b;
		scanf("%d", & b);
		for (int j = b; j != 1; j /= 2) {
			if (buf[j] == 0) {
				upgrade(j, -1);
			}
			ans -= abs(buf[j]);
			buf[j]--;
			ans += abs(buf[j]);
		}
		int x = pre_mn[1];
		a[x]--;
		update(x);
		for (int j = x; j != 1; j /= 2) {
			if (buf[j] == -1) {
				upgrade(j, 1);
			}
			ans -= abs(buf[j]);
			buf[j]++;
			ans += abs(buf[j]);
		}
		printf("%d ", ans);
	}
	return 0;
}
