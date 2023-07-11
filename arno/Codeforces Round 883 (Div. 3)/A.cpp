#include "bits/stdc++.h"

using namespace std;

int main() {
	int T; cin >> T;
	while(T --) {
		int a, b, n, ans = 0;
		cin >> n;
		while(n --) {
			scanf("%d %d", &a, &b);
			if(a > b) {
				ans ++;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
