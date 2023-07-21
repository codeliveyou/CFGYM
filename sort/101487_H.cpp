#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;
using LL = long long;
using VI = vector < int > ;
using pii = pair < int, int > ;

struct tree {
	vector < set < pii >> elems;
	vector < pii > minY;
	VI maxY;
	int len, count;

	void init(int n) {
		for (len = 1; len < n; len *= 2);
		elems.assign(len, {});
		minY.assign(len * 2, {
			INT_MAX,
			-1
		});
		maxY.assign(len * 2, INT_MIN);
		count = 0;
	}

	void updateMin(int i) {
		if (elems[i].empty()) {
			minY[i + len] = {
				INT_MAX,
				-1
			};
		} else {
			minY[i + len] = {
				elems[i].begin() -> x,
				i
			};
			maxY[i + len] = max(maxY[i + len], elems[i].rbegin() -> x);
		}

		i += len;

		while (i /= 2) {
			minY[i] = min(minY[i * 2], minY[i * 2 + 1]);
			maxY[i] = max(maxY[i * 2], maxY[i * 2 + 1]);
		}
	}

	void add(pii p, int i) {
		count += elems[p.x].insert({
			p.y,
			i
		}).y;
		updateMin(p.x);
	}

	void del(pii p, int i) {
		count -= int(elems[p.x].erase({
			p.y,
			i
		}));
		updateMin(p.x);
	}

	bool has_over(pii p) {
		return queryMax(p.x, len, 1, 0, len) >= p.y;
	}

	int get_under(pii q) {
		pii p = queryMin(0, q.x + 1, 1, 0, len);
		if (p.x <= q.y) {
			return elems[p.y].begin() -> y;
		} else {
			return -1;
		}
	}

	int queryMax(int vb, int ve, int i, int b, int e) {
		if (vb >= e || b >= ve) {
			return INT_MIN;
		}
		if (b >= vb && e <= ve) {
			return maxY[i];
		}
		int m = (b + e) / 2;
		return max(queryMax(vb, ve, i * 2, b, m), queryMax(vb, ve, i * 2 + 1, m, e));
	}

	pii queryMin(int vb, int ve, int i, int b, int e) {
		if (vb >= e || b >= ve) {
			return {
				INT_MAX,
				-1
			};
		}
		if (b >= vb && e <= ve) {
			return minY[i];
		}
		int m = (b + e) / 2;
		return min(queryMin(vb, ve, i * 2, b, m), queryMin(vb, ve, i * 2 + 1, m, e));
	}
};

vector < LL > uniqueVector(vector < LL * > & vec) {
	sort(vec.begin(), vec.end(), [](LL * l, LL * r) {
		return * l < * r;
	});
	vector < LL > pre;
	for (auto e: vec) {
		if (pre.empty() || pre.back() != * e) {
			pre.push_back( * e);
		}
		* e = pre.size() - 1;
	}
	return pre;
}

tree nails[2][2];

void solve() {
	int n;
	cin >> n;
	vector < pair < LL, LL >> points[2];
	vector < bool > isWide;

	for (int i = 0; i < n; i++) {
		LL x, y;
		cin >> x >> y;
		char t;
		cin >> t;
		points[0].push_back({
			x * 2 + y,
			y - x * 2
		});
		points[1].push_back({
			x + y,
			y - x
		});
		isWide.push_back(t == 'W');
	}

	for (int j = 0; j < 2; j++) {
		auto & ps = points[j];
		vector < LL * > xc(ps.size()), yc(ps.size());

		for (int i = 0; i < ps.size(); i++) {
			xc[i] = & ps[i].x;
			yc[i] = & ps[i].y;
		}

		int nx = uniqueVector(xc).size();
		uniqueVector(yc);
		nails[j][0].init(nx + 5);
		nails[j][1].init(nx + 5);
	}

	for (int i = 0; i < n; i++) {
		pii p[2] = {
			points[0][i],
			points[1][i]
		};
		int t = isWide[i];

		if (nails[0][0].has_over(p[0]) || nails[1][1].has_over(p[1])) {
			cout << "FAIL\n";
			continue;
		}

		for (int j = 0; j < 2; j++) {
			while (true) {
				int ind = nails[t][j].get_under(p[t]);
				if (ind == -1) {
					break;
				}
				nails[0][j].del(points[0][ind], ind);
				nails[1][j].del(points[1][ind], ind);
			}
		}

		nails[0][t].add(p[0], i);
		nails[1][t].add(p[1], i);

		cout << nails[0][0].count + nails[0][1].count << '\n';
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("inputdata.txt", "r", stdin);
	//	freopen("outputdata.txt", "w", stdout);
	#endif
	cin.sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
