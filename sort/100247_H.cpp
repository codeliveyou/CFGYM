#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
char s[N], t[N];

int main() {
	int n;
	scanf("%d %s %s", &n, s, t);
	int ans = 0;
	for(int i = 0, j; i < n; i = j) {
		for(j = i; j < n && (s[j] == t[j]) == (s[i] == t[i]); j ++);
		if(s[i] != t[i]) {
			ans ++;
		}
	}
	cout << ans << endl;
	return 0;
}
