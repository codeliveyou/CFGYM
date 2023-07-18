#include <bits/stdc++.h>

using namespace std;
using DO = double;
const int N = 1e5 + 10;
const double pi = acos(-1);

struct Point {
	DO x, y;
	int id;
	Point(DO x = 0, DO y = 0, int id = -1): x(x), y(y), id(id) {};
	bool operator < (Point p) const {
		return tie(x, y) < tie(p.x, p.y);
	}
	bool operator == (Point p) const {
		return tie(x, y) == tie(p.x, p.y);
	}
	Point operator + (Point p) const {
		return Point(x + p.x, y + p.y);
	}
	Point operator - (Point p) const {
		return Point(x - p.x, y - p.y);
	}
	Point operator * (DO d) const {
		return Point(x * d, y * d);
	}
	Point operator / (DO d) const {
		return Point(x / d, y / d);
	}
	DO dot(Point p) const {
		return x * p.x + y * p.y;
	}
	DO cross(Point p) const {
		return x * p.y - y * p.x;
	}
	DO cross(Point a, Point b) const {
		return (a - * this).cross(b - * this);
	}
	DO dist2() const {
		return x * x + y * y;
	}
	double dist() const {
		return sqrt((double) dist2());
	}
	double angle() const {
		return atan2(y, x);
	}
	Point perp() const {
		return Point(-y, x);
	}
	friend ostream & operator << (ostream & os, Point p) {
		return os << p.id << "#" << "(" << p.x << "," << p.y << ")";
	}
};

struct circle {
	Point center;
	double r;
	circle(Point center, double r): center(center), r(r) {}
};

int n;
vector < circle > P;

pair < double, double > add(int np) {
	double delta = 2 * pi / np;
	double ans = 0;
	double angle = -delta;
	double area = 0;
	Point p;
	for (int c = 0; c <= np; ++c) {
		double max_in_direction = -1e18;
		double co = cos(angle), si = sin(angle);
		Point cur_unit(co, si);
		Point most_aligned;

		for (int i = 0; i < n; ++i) {
			Point cur = P[i].center;
			cur.x += P[i].r * co;
			cur.y += P[i].r * si;
			double cur_in_direction = cur.dot(cur_unit);
			if (cur_in_direction > max_in_direction) {
				max_in_direction = cur_in_direction;
				most_aligned = cur;
			}
		}

		if (c > 0) {
			ans += (p - most_aligned).dist();
			area += p.cross(most_aligned);
		}

		p = most_aligned;
		angle += delta;
	}
	area = abs(area) / 2;
	return {
		ans,
		area
	};
}

double calc(vector < double > A) {
	vector < double > diffs(2);
	for (int i = 0; i < 2; ++i) {
		diffs[i] = A[i + 1] - A[i];
	}
	double ratio = diffs.back() / diffs.front();
	double inv_ratio = 1 - ratio;
	double ans = A.front() + diffs.front() / inv_ratio;
	return ans;
}

void solve() {
	cin >> n;
	P.clear();
	for (int i = 0; i < n; ++i) {
		Point p;
		p.id = i;
		double r;
		cin >> p.x >> p.y >> r;
		P.push_back({
			p,
			r
		});
	}
	int split = 900;
	vector < double > L(3);
	vector < double > A(3);
	for (int i = 0; i < 3; ++i) {
		pair < double, double > cur = add(split);
		L[i] = cur.first;
		A[i] = cur.second;
		split *= 5;
	}
	cout << setprecision(12) << fixed << calc(L) << ' ' << calc(A) << endl;
}

int main() {
	solve();
	return 0;
}
