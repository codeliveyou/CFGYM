#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;

const int mod = 998244353;
const LD eps = 1e-10;

struct point {
	LL x, y;
	point(LL x = 0, LL y = 0) : x(x), y(y) {}

	point operator - (const point & a) const {
		return point(x - a.x, y - a.y);
	}

	point operator + (const point & a) const {
		return point(x + a.x, y + a.y);
	}

	point operator * (const LL & a) const {
		return point(x * a, y * a);
	}

	LL operator * (const point & a) const {
		return x * a.x + y * a.y;
	}

	LL operator ^ (const point & a) const {
		return x * a.y - y * a.x;
	}

	LL len2() const {
		return x * x + y * y;
	}

	LD len() const {
		return sqrtl(len2());
	}

	point rotate() const {
		return point(-y, x);
	}

	int pos() const {
		return y < 0 || (y == 0 && x < 0);
	}
	
	void input() {
		scanf("%I64d %I64d", &x, &y);
	}
};

int sign(LL x) {
	return (x > 0) - (x < 0);
}

LD intersection_distance(const point& a, const point& b, const point& c, const point& d) {
	LL pr = (d - c) ^ (b - a);
	if (pr == 0) 
		return min((c - a) * (b - a), (d - a) * (b - a)) / (b - a).len();
	return (b - a).len() * ((d - a) ^ (c - a)) / pr;
}

bool is_in_polygon(const vector<point>& p, const point& a, const point& b) {
	int n = p.size();
	vector<pair<LD, int>> events;
	for(int i = 0; i < n; i++) {
		int x = sign((b - a) ^ (p[i] - a));
		int y = sign((b - a) ^ (p[(i + 1) % n] - a));
		if (x == y) {
			continue;
		}
		events.emplace_back(intersection_distance(a, b, p[i], p[(i + 1) % n]), (x < y ? 1 : -1) * (x != 0 && y != 0 ? 2 : 1));
	}
	sort(events.begin(), events.end());
	LD ans = 0;
	LD cur = 0;
	int bal = 0;
	LD len = (b - a).len();
	for(int i = 0; i < (int)events.size(); i++) {
		if(bal != 0) {
			cur += events[i].first - events[i - 1].first;
			ans = max(ans, cur);
		} else {
			if (i != 0 && events[i].first <= len + eps && events[i - 1].first >= -eps) {
				return false;
			}
			cur = 0;
		}
		bal += events[i].second;
	}
	return true;
}

void add(int & a, const int & b) {
	a += b;
	if(a >= mod) {
		a -= mod;
	}
}

int main() {
	int n; scanf("%d", &n);
	vector<point> p(n);
	for (int i = 0; i < n; i++) {
		p[i].input();
	}
	vector<pair<int, int>> edge;
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			if(is_in_polygon(p, p[i], p[j])) {
				edge.push_back({i, j});
				edge.push_back({j, i});
			}
		}
	}
	sort(edge.begin(), edge.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
		point x = p[a.second] - p[a.first];
		point y = p[b.second] - p[b.first];
		if(x.pos() != y.pos()) return x.pos() < y.pos();
		if(x ^ y) return (x ^ y) > 0;
		return (x * p[a.first]) < (x * p[b.first]);
	});
	int ans = 0;
	for(int i = 0; i < n; i++) {
		vector<vector<int>> dp(n, vector<int>(2));
		dp[i][0] = 1;
		for(auto a : edge) {
			int x = a.first, y = a.second;
			add(dp[y][1], dp[x][1]);
			if((p[x] - p[i]) ^ (p[y] - p[x])) {
				add(dp[y][1], dp[x][0]);
			} else if ((p[x] - p[i]) * (p[y] - p[x]) >= 0) {
				add(dp[y][0], dp[x][0]);
			}
		}
		add(ans, dp[i][1]);
		for(int j = 0; j < n; j++) {
			if(p[j].y > p[i].y || (p[j].y == p[i].y && p[j].x > p[i].x)) {
				add(ans, dp[j][0]);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
