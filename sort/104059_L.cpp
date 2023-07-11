#include <bits/stdc++.h>
using namespace std;
int main() {
	int l, w, n;
	scanf("%d %d %d", &l, &w, &n);
	if ((l * w) % n) {
		puts("impossible");
	}
	else {
		int g = __gcd(l, n);
		int ww = n / g;
		int L = l / g;
		int W = w / ww;
		for (int i = 0; i < l; i ++) {
			for (int j = 0; j < w; j ++) {
				putchar('A' + (i / L) * ww + j / W);
			}
			cout << "\n";
		}
	}
	return 0;
}
