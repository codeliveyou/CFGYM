#include<bits/stdc++.h>
using namespace std;

struct point {
	int x, y;
	point(int x = 0, int y = 0) : x(x), y(y) {}
	point operator - (const point & a) {
		return point(x - a.x, y - a.y);
	}
	int operator ^ (const point & a) {
		return x * a.y - y * a.x;
	}
	int len2() {
		return x * x + y * y;
	}
	double get_cos(point a, point b) {
		return ((a - *this).len2() + (b - *this).len2() - (a - b).len2()) / (2 * sqrt(1. * (a - *this).len2() * (b - *this).len2()));
	}
	void input() {
		scanf("%d %d", &x, &y);
	}
};

const int N = 1e6 + 10;
point p[N];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++) {
		p[i].input();
	}
	
	int c = 1, b = 2, a = 0;
	for(int i = 3; i <= n; i ++) {
		if((p[i] - p[c]).len2() < (p[b] - p[c]).len2()) {
			b = i;
		}
	}
	
	double min_cos_a = 1, tmp;
	for(int i = 2; i <= n; i ++) {
		if(i != b) {
			if(p[b] - p[c] ^ p[i] - p[c]) {
				if((tmp = p[i].get_cos(p[b], p[c])) < min_cos_a) {
					min_cos_a = tmp;
					a = i;
				}
			}
		}
	}
	
	if(a) {
		puts("Yes");
		printf("%d %d %d\n", c, b, a);
	}
	else {
		puts("No");
	}
	return 0;
}
