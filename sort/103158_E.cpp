#include <bits/stdc++.h>
using namespace std;

const int N = 888;
int a[N];

int solve() {
	int n, l, r;
	scanf("%d %d %d", &n, &l, &r);
	
	for(int i = 0; i < n; i ++) {
		scanf("%d", a + i);
	}
	
	int ans, lcm = 0;
	
	for(int i = r; i >= l && lcm <= i; i --) {
		int g = 0;
		for(int j = 0; j < n; j ++) {
			g = __gcd(g, i / __gcd(i, a[j]));
			if(g <= lcm) break;
		}
		if(lcm < g) {
			lcm = g;
			ans = i;	
		}
	}
	
	return ans;
}

int main() {
	freopen("lcm.in", "r", stdin);
	int T; cin >> T;
	while(T --) {
		cout << solve() << endl;
	}
	return 0;
}
