#include <bits/stdc++.h>

using namespace std;


int p[50];
vector<int> v[50];

int solve(int n) {
	for(int i = 0; i < n; i ++) {
		p[i] = i;
		v[i].resize(n);
		for(auto & x : v[i]) x = 0;
	}
	set<vector<int>> st;
	do {
		bool bad = false;
		for(int i = 2; i <= n; i ++) {
			if(p[(i / 2) - 1] > p[i - 1]) {
				bad = true;
				break;
			}
		}
		if(bad) continue;
		for(int i = 0; i < n; i ++) {
			v[p[i]][i] = 1;
		}
	} while(next_permutation(p, p + n));
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++) cout << v[i][j] << ' ';
		cout << endl;
	}
	for(int i = 0; i < n; i ++) {
		st.insert(v[i]);
	}
	return st.size();
}

int main() {
//	for(int i = 1; i < 20; i ++) cout << i << ' ' << __builtin_popcount(i) << endl; return 0;
	for(int i = 1; i < 13; i ++) {
		cout << i << ' ' << solve(i) << endl << endl;
	}
	return 0;
}
