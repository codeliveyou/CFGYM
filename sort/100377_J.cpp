#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using LL = long long;
using pii = pair<int, int>;

const int N = 1e5 + 10;

#define F(x) (a[i] * b[x] + f[x])
#define G(x, y) ((f[y] - f[x]) / (b[x] - b[y] + 0.0))

int q[N], prv[N];
LL a[N], b[N], f[N];
pii p[N], pp[N], rect[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("inputdata.txt", "r", stdin);
#endif
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) {
		scanf("%d %d", &rect[i].x, &rect[i].y);
	}
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i ++) {
		int j = i - 1;
		while (j && p[j].second <= p[i].second) j = prv[j];
		prv[i] = j;
	}
	int cnt = 0;
	for (int i = n; i; i = prv[i]) pp[++cnt] = p[i];
	reverse(pp + 1, pp + cnt + 1);
	for (int i = 1; i <= cnt; i ++) a[i] = pp[i].first, b[i-1] = pp[i].second;
	int h = 1, t = 0;
	for (int i = 1; i <= cnt; i ++) {
		while (h < t && F(q[h]) >= F(q[h+1])) h ++;
		f[i] = min(F(0), F(q[h]));
		while (h < t && G(q[t-1], q[t]) >= G(q[t], i)) t --;
		q[++t] = i;
	}
	printf("%I64d\n", f[cnt]);
	return 0;
}
