#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("inputdata.txt", "w", stdout);
	int n = 100;
	for(int i = 1; i <= n; i ++) {
		printf("%d %d %d\n", (rand() % 2000) - 1000, (rand() % 2000) - 1000, (rand() % 50) + 1);
	}
	return 0;
}
