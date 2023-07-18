#include<bits/stdc++.h>
using namespace std;

using LL = long long;

void put(LL x, LL y, LL z) {
	puts("YES");
	cout << x << ' ' << y << ' ' << z << endl;
}

int main() {
	LL t, a, c, b;
	cin >> t;
	while(t --) {
		cin >> a >> b >> c;
		if(a == 0 && b == 0 && c == 0) {
			put(1, 1, 1);
		}
		else if(a == b && b == c) {
			puts("NO");
		}
		else if(a > c) {
			c = c + b / a * a + a + a;
			put(a, b + c, c);
		}
		else if(c > b) {
			b = b + a / c * c + c + c;
			put(a + b, b, c);
		}
		else if(b > a) {
			a = a + c / b * b + b + b;
			put(a, b, a + c);
		}
	}
	return 0;
}
