#include <bits/stdc++.h>

#define x first
#define y second
using namespace std;

using DO = double;

vector < pair < DO, DO > > ban;

int main() {
	#ifdef ONLINE_JUDGE
	freopen("magicbox.in", "r", stdin);
	freopen("magicbox.out", "w", stdout);
	#endif
	int n;
	DO D, L;
	cin >> n >> D >> L;
	DO R = D / 2;
	for (int i = 1; i <= n; i++) {
		char typ;
		DO x, y;
		cin >> typ >> x >> y;
		ban.push_back({
			x - sqrt(y * (D - y)),
			min(L, x + sqrt(y * (D - y)))
		});
	}
	ban.push_back({
		0,
		R
	});
	ban.push_back({
		L - R,
		L
	});
	sort(ban.begin(), ban.end());
	DO mx = R;
	for (int i = 0; i < ban.size(); i++) {
		if (mx > L - R) {
			break;
		}
		if (mx <= ban[i].x) {
			puts("YES");
			return 0;
		}
		mx = max(mx, ban[i].y);
	}
	puts("NO");
	return 0;
}
