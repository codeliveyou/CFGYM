#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
using LL = unsigned long long;
using pii = pair<int, int>;

const int N = 1e6;

int ax[N], ay[N], bx[N], by[N], w[N], numbers_can_eat[N];
vector<int> beagles_can_eat_this[N];

bool solve() {
	int n, m;
	LL s;
	cin >> n >> m >> s;
	if(s < 10) {
		return 0;
	}
	s -= 10;
	for(int i = 0; i < n; i ++) {
		scanf("%d %d", ax + i, ay + i);
	}
	for(int i = 0; i < m; i ++) {
		scanf("%d %d %d", bx + i, by + i, w + i);
	}
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m; j ++) {
			if(s * s >= (LL)(ax[i] - bx[j]) * (ax[i] - bx[j]) + (LL)(ay[i] - by[j]) * (ay[i] - by[j])) {
				beagles_can_eat_this[j].push_back(i);
				numbers_can_eat[i] ++;
			}
		}
	}
	for(int i = 0; i < m; i ++) {
		sort(beagles_can_eat_this[i].begin(), beagles_can_eat_this[i].end(), [&](int b1, int b2) {
			if(numbers_can_eat[b1] == -1) {
				return false;
			}
			if(numbers_can_eat[b2] == -1) {
				return true;
			}
			return numbers_can_eat[b1] < numbers_can_eat[b2];
		});
		for(int j = 0; j < beagles_can_eat_this[i].size() && j < w[i]; j ++) {
			numbers_can_eat[beagles_can_eat_this[i][j]] = -1;
		}
	}
	for(int i = 0; i < n; i ++) {
		if(numbers_can_eat[i] != -1) {
			return 0;
		}
	}
	return 1;
}

int main() {
	if(solve()) {
		puts("YES");
	}
	else {
		puts("NO");
	}
	return 0;
}
