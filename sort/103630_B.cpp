#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10;

int max_height[N];
int passed[2][N];

int main() {
	fill(max_height, max_height + N, 1);
	for(int i = 1; i * i < N; i ++) {
		for(int j = 1; 2 * i + j < N; j ++) {
			for(int k = 2, m; (m = k * i + k * (k - 1) / 2 * j) < N; k ++) {
				if(max_height[m] < k) {
					max_height[m] = k;
				}
			}
		}
	}
	
	int n, ans = 0;
	scanf("%d", &n);
	
	passed[0][1] = 1;
	while(n--) {
		fill(passed[1], passed[1] + N, 0);
		
		int type, m;
		cin >> type >> m;
		
		while(m --) {
			int k;
			cin >> k;
			int d = type == 1 ? k : -k;
			for(int j = 0; j < N; j++) {
				if(0 < j - d && j - d < N) {
					passed[1][j] |= passed[0][j - d];
				}
			}
		}
		
		for(int i = 0; i < N; i ++) {
			passed[0][i] = passed[1][i];
		}
	}

	for(int i = 1; i < N; i++) {
		if(passed[0][i] && ans < max_height[i]) {
			ans = max_height[i];
		}
	}
	
	printf("%d\n", ans);
	return 0;
}
