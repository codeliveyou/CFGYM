#include "bits/stdc++.h"

int main() {
	srand(time(0));
	freopen("in1.txt", "w", stdout);
	int n = 1e5;
	printf("%d\n", n);
	for(int i = 1; i < n; i ++) {
		printf("%d%c", (rand() & 1) ? 5 : 1, " \n"[i == n - 1]);
	}
	for(int i = 1; i < n; i ++) {
		printf("%d%c", (rand() & 1) ? 5 : 1, " \n"[i == n - 1]);
	}
	int q = 1e5;
	printf("%d\n", q);
	for(int i = 0; i < q; i ++) {
		for(int j = 0; j < 4; j ++) {
			printf("%d%c", 1ll * rand() * rand() % n + 1, " \n"[j == 3]);
		}
	}
	return 0;
}
