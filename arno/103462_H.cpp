#include <bits/stdc++.h>
using namespace std;

const int mx = 1123456;

void solve () {
	int x, y;
	cin >> x >> y;
	vector<pair<int, int>> ans;
	int dx = abs(x), dy = abs(y);
	bool negX = x < 0, negY = y < 0;
	int iter = 1;
	x = 0, y = 0;
	while (x != dx || y != dy) {
		int pos = iter;
		int delta = min(pos, dx - x);
		x += delta;
		pos -= delta;
		delta = min(pos, dy-y);
		y += delta;
		pos -= delta;
		
		if (x == dx && y == dy && pos > 0) {
		  y += pos % 2;
		}
		ans.emplace_back(x, y);
		iter++;
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i ++) {
		cout << (1 - 2*negX)*ans[i].first << " " << (1 - 2*negY)*ans[i].second << endl;
	}
}

int main () {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cout << "Case #" << i+1 << ":" << endl;
		solve();
	}
	return 0;
}
