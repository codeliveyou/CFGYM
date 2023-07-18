#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;
using LL = long long;
using pii = pair < int, LL > ;
using VP = vector < pii > ;

VP val[2], chunk[2];

int main() {
	LL tot_len[2] = {
		0,
		0
	};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			LL x;
			cin >> x;
			tot_len[i] += x;
			val[i].push_back({
				((j + 1) & 1),
				x
			});
		}
	}
	if (tot_len[0] < tot_len[1]) {
		val[0].insert(val[0].begin(), {
			0,
			tot_len[1] - tot_len[0]
		});
	} else if (tot_len[1] < tot_len[0]) {
		val[1].insert(val[1].begin(), {
			0,
			tot_len[0] - tot_len[1]
		});
	}
	while (val[0].size() && val[1].size()) {
		LL q = min(val[0].back().y, val[1].back().y);
		chunk[0].push_back({
			val[0].back().x,
			q
		});
		chunk[1].push_back({
			val[1].back().x,
			q
		});
		val[0].back().y -= q;
		if (val[0].back().y == 0) {
			val[0].pop_back();
		}
		val[1].back().y -= q;
		if (val[1].back().y == 0) {
			val[1].pop_back();
		}
	}
	int over_flow = 0;
	VP ans;
	for (int a = 0; a < chunk[0].size(); a++) {
		LL x = chunk[0][a].x, y = chunk[1][a].x, q = chunk[0][a].y;
		if (x == 0 && y == 0) {
			if (over_flow == 0) {
				ans.push_back({
					0,
					q
				});
			} else {
				ans.push_back({
					1,
					1
				});
				if (q > 1) {
					ans.push_back({
						0,
						q - 1
					});
				}
			}
			over_flow = 0;
		} else if (x == 1 && y == 1) {
			if (over_flow == 0) {
				ans.push_back({
					0,
					1
				});
				if (q > 1) {
					ans.push_back({
						1,
						q - 1
					});
				}
			} else {
				ans.push_back({
					1,
					q
				});
			}
			over_flow = 1;
		} else {
			if (over_flow == 0) {
				ans.push_back({
					1,
					q
				});
			} else {
				ans.push_back({
					0,
					q
				});
			}
		}
	}
	if (over_flow) {
		ans.push_back({
			1,
			1
		});
	}
	reverse(ans.begin(), ans.end());
	for (int i = 0, j; i < ans.size(); i = j) {
		for (j = i + 1; j < ans.size() && ans[i].x == ans[j].x;) {
			ans[i].y += ans[j].y;
			j++;
		}
		printf("%I64d ", ans[i].y);
	}
	return 0;
}
