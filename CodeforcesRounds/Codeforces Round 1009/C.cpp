#include <bits/stdc++.h>
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	int T; cin >> T;
	while(T --) {
		int n; scanf("%d", &n);
		int a = -1;
		int b = -1;
		for(int i = 0; (1 << i) < n; i ++) {
			if(0 == (n & (1 << i))) {
				if(a == -1) a = 1 << i;
			}
			else {
				if(b == -1) b = 1 << i;
			}
		}
		int answer = -1;
		if(a != -1 && b != -1) answer = a + b;
		if(answer > n) answer = -1;
		printf("%d\n", answer);
//		cout << answer << ' ' << n << ' ' << (n ^ answer) << endl;
	}
	return 0;
}