#include<bits/stdc++.h>

using namespace std;

int main() {
	
	srand(time(0));
	
	int n = 10, m = 20, k = 10;
	printf("%d %d %d\n", n, m, k);
	set<pair<int, int>> st;
	for(int i = 0; i < m; i ++) {
		int u, v;
		while((u = rand() % 10 + 1) == (v = rand() % 10 + 1) or st.count({u, v}));
		st.insert({u, v});
		st.insert({v, u});
		cout << u << ' ' << v << endl;
	}
	
	cout << 10 << endl;
	int p[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, };
	random_shuffle(p, p + 10);
	for(int i = 0; i < 10; i ++) {
		int t = rand() % 2 + 1;
		cout << t << ' ' << p[i] << endl;
	}
	
	return 0;
}
