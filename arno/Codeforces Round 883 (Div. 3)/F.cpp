#include "bits/stdc++.h"

using namespace std;
using LL = long long;

const LL inf = 1e18;

set<LL> st;

bool ok(LL x, LL y) {
	return x <= inf / y;
}

bool is(LL x) {
	LL st = 2, ed = 1e9;
	while(st + 1 < ed) {
		LL md = (st + ed) >> 1;
		if(1 + md + md * md <= x) {
			st = md;
		}
		else {
			ed = md;
		}
	}
	return 1 + st + st * st == x;
}

int main() {
	for(LL k = 2; k <= 1000000; k ++) {
		LL tmp = 1 + k + k * k;
		LL x = k * k;
		while(ok(x, k)) {
			x *= k;
			tmp += x;
			st.insert(tmp);
		}
	}
	int T; cin >> T;
	while(T --) {
		LL x;
		scanf("%I64d", &x);
		if(st.count(x)) {
			puts("YES");
		}
		else {
			puts(is(x) ? "YES" : "NO");
		}
	}
	return 0;
}
