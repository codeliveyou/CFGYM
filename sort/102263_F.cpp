#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

int a[N], b[N], c[N];

bool flag[N], dp[N][N];

int main() {
	int n, pos;
	scanf("%d %d", &n, &pos);
	for(int i = 1; i < n; i ++) {
		scanf("%d", a + i);
	}
	for(int i = 1; i < n; i ++) {
		scanf("%d", b + i);
		for(int j = 1; j < b[i]; j ++) {
			if(!flag[j]) {
				c[i] ++;
			}
		}
		flag[b[i]] = 1;
	}
	dp[0][pos - 1] = 1;
	for(int j = 1; j < n; j ++) {
		int P = n - j + 1;
		for(int i = 0; i < c[j]; i ++) {
			if(dp[j - 1][(i + a[j]) % P]) {
				dp[j][i] = 1;
			}
			if(dp[j - 1][((i - a[j]) % P + P) % P]) {
				dp[j][i] = 1;
			}
		}
		for(int i = c[j]; i < n - j; i ++) {
			if(dp[j - 1][(i + 1 + a[j]) % P]) {
				dp[j][i] = 1;
			}
			if(dp[j - 1][((i + 1 - a[j]) % P + P) % P]) {
				dp[j][i] = 1;
			}
		}
	}
	if(dp[n - 1][0]) {
		puts("Yes");
	}
	else {
		puts("No");
	}
	return 0;
}
