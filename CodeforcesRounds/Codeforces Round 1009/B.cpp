#include <bits/stdc++.h>
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int T; cin >> T;
	while(T --) {
		int n; scanf("%d", &n);
		int s = 0;
		for(int i = 0; i < n; i ++) {
			int a;
			scanf("%d", &a);
			s += a;
		}
		printf("%d\n", s - (n - 1));
	}
	return 0;
}