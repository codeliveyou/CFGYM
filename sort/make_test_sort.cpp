#include <bits/stdc++.h>

using namespace std;
const int N = 1e4;
int a[N];
int main() {
	freopen("inputdata-100699N8_1.txt", "w", stdout);
	srand(time(0));
	int n = 100;
	cout << n << endl;
	for(int i = 1; i <= n; i ++) {
		a[i] = i;
	}
	random_shuffle(a + 1, a + n + 1);
	for(int i = 1; i <= n; i ++) {
		cout << a[i] << endl;
	}
	return 0;
}
