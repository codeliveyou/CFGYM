#include "bits/stdc++.h"
using namespace std;


struct Point {
	int x, y;
	Point(int x = 0, int y = 0) : x(x), y(y) {}
	long long distance(const Point & a) {
		return 1ll * (x - a.x) * (x - a.x) + 1ll * (y - a.y) * (y - a.y);
	}
	void input() {
		scanf("%d %d", &x, &y);
	}
	void print() {
		printf("%d %d\n", x, y);
	}
};

const int NMAX = 3010;

Point P[NMAX];
long long dist_origin[NMAX];
long long dist_changed[NMAX];
int N, Q;

void solution() {
	int changed_id;
	scanf("%d", &changed_id);
	Point origin = P[changed_id];
	P[changed_id].input();
	
	for(int i = 0; i < N; i ++) {
		dist_origin[i] = origin.distance(P[i]);
		dist_changed[i] = P[changed_id].distance(P[i]);
	}
	
	dist_origin[changed_id] = 0;
	dist_changed[changed_id] = 0;
	
	sort(dist_origin, dist_origin + N);
	sort(dist_changed, dist_changed + N);
	
	for(int i = 0; i < N; i ++) {
		if(dist_origin[i] != dist_changed[i]) {
			if(dist_origin[i] < dist_changed[i]) {
				puts("larger");
			}
			else {
				puts("smaller");
			}
			return;
		}
	}
	
	puts("equal");
}

int main() {
	cin >> N >> Q;
	
	for(int i = 0; i < N; i ++) {
		P[i].input();
	}
	
	while(Q --) {
		solution();
	}
	
	return 0;
}
