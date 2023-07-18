#include <bits/stdc++.h>
using namespace std;
using LL = long long;

vector<pair<LL, LL>> p;
set<pair<LL, int>> st;

int main() {
	
//	int n = 1000;
//	int r = 2;
//	int w = 1000000000;
//	int h = w;
//	freopen("input.txt", "w", stdout);
//	cout << n << ' ' << r << ' ' << w << ' ' << h << endl;
//	for(int i = 0; i < n; i ++) {
//		printf("%d %d\n", 1ll * rand() * rand() % w, 1ll * rand() * rand() % w);
//	}
	freopen("input.txt", "r", stdin);
	int n, r, w, h;
	cin >> n >> r >> w >> h;
	for(int i = 0; i < n; i ++) {
		int x, y;
		scanf("%d %d", &x, &y);
		p.push_back({y + 1ll * x * r, y - 1ll * x * r});
	}
	sort(p.begin(), p.end());
	int mx = 0;
	for(auto a : p) {
		st.insert({a.second, ++ mx});
		auto it = st.find({a.second, mx});
		it ++;
		if(it != st.end()) {
			st.erase(it);
		}
	}
	printf("%d\n", st.size());
	return 0;
}
