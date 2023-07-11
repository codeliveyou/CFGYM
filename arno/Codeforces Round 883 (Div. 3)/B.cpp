#include "bits/stdc++.h"

using namespace std;
using pii = pair<int, int>;
#define x first
#define y second

char s[5][5];

vector<vector<pii>> p;


void solve() {
	for(int i = 0; i < 3; i ++) {
		scanf("%s", s[i]);
	}
	for(auto r : p) {
		bool ok = true;
		for(int i = 1; i < 3; i ++) {
			if(s[r[0].x][r[0].y] != s[r[i].x][r[i].y]) {
				ok = false;
			}
		}
		if(ok && s[r[0].x][r[0].y] != '.') {
			printf("%c\n", s[r[0].x][r[0].y]);
			return;
		}
	}
	puts("DRAW");
}

int main() {
	for(int i = 0; i < 3; i ++) {
		vector<pii> tmp;
		for(int j = 0; j < 3; j ++) {
			tmp.push_back({i, j});
		}
		p.push_back(tmp);
		tmp.clear();
		for(int j = 0; j < 3; j ++) {
			tmp.push_back({j, i});
		}
		p.push_back(tmp);
	}
	vector<pii> tmp;
	for(int i = 0; i < 3; i ++) {
		tmp.push_back({i, i});
	}
	p.push_back(tmp);
	tmp.clear();
	for(int i = 0; i < 3; i ++) {
		tmp.push_back({i, 2 - i});
	}
	p.push_back(tmp);
	
	int T; cin >> T;
	while(T --) {
		solve();
	}
	return 0;
}
