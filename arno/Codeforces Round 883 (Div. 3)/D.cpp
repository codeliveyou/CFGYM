#include "bits/stdc++.h"

using namespace std;
const int N = 2e5 + 10;

int hei[N];

long double calc(long double h1, long double h2, long double d, long double h) {
	long double H = min(h, h2 - h1);
	long double suf = d * (h - H) / h;
	return (suf + d) * H / 2;
}

long double solve() {
	int n, d, h;
	cin >> n >> d >> h;
	for(int i = 0; i < n; i ++) {
		scanf("%d", hei + i);
	}
	long double ans = 0;
	hei[n] = hei[n - 1] + h;
	for(int i = n - 1; i >= 0; i --) {
		ans += calc(hei[i], hei[i + 1], d, h);
	}
	return ans;
}

int main() {
	int T; cin >> T;
	cout << setprecision(10) << fixed;
	while(T --) {
		cout << solve() << endl;
	}
	return 0;
}
