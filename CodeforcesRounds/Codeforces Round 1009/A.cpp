#include <bits/stdc++.h>
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int T; cin >> T;
	while(T --) {
		int a, b, c, d;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		puts(a == b && b == c && c == d ? "YES" : "NO");
	}
	return 0;
}