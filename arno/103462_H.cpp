#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
using pii = pair<int, int>;
vector<pii> ans;

void solve (int tcase) {
	int x, y;
	scanf("%d %d", &x, &y);
	int dx = x, dy = y;
	int X = 1, Y = 1;
	if (x < 0) {
		dx = -x;
		X = -1;
	}
	if (y < 0) {
		dy = -y;
		Y = -1;
	}
	x = y = 0;
	for (int step = 1; x != dx || y != dy; step ++) {
		int pos = step, d = min(pos, dx - x);
		x += d;
		pos -= d;
		d = min(pos, dy - y);
		y += d;
		pos -= d;
		if (x == dx && y == dy && pos > 0) {
		  y += pos % 2;
		}
		ans.push_back({x, y});
	}
	printf("Case #%d:\n%d\n", tcase, ans.size());
	for(auto a : ans) {
		printf("%d %d\n", a.x * X, a.y * Y);
	}
	ans.clear();
}

int main () {
	int T;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		solve(i);
	}
	return 0;
}
