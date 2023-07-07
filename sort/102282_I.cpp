#include <bits/stdc++.h>
using namespace std;

int n, x[12], y[12], multi[12], used[12];
set<int> flag;
int ans[12][12];

bool dfs(int cur_id) {
	if (cur_id == n + 1) {
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= n; j ++) {
				printf("%d%c", ans[i][j], j == n ? '\n' : ' ');
			}
		}
		return true;
	}
	for(int k = 1; k * k < y[cur_id]; k ++) {
		if(y[cur_id] % k) {
			continue;
		}
		int u = k, v = y[cur_id] / k;
		if(flag.count(u) || flag.count(v)) {
			continue;
		}
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= n; j ++) {
				if(i == j
				 || (used[i] == 2 || used[j] == 2)
				 || (used[i] == 1 && multi[i] * u != x[i])
				 || (used[j] == 1 && multi[j] * v != x[j])
				 || (used[i] == 0 && x[i] % u != 0)
				 || (used[j] == 0 && x[j] % v != 0)
				 ) {
					continue;
				}
				flag.insert(u);
				flag.insert(v);
				used[i] ++;
				used[j] ++;
				multi[i] *= u;
				multi[j] *= v;
				ans[cur_id][i] = u;
				ans[cur_id][j] = v;
				if(dfs(cur_id + 1)) {
					return true;
				}
				flag.erase(u);
				flag.erase(v);
				used[i] --;
				used[j] --;
				multi[i] /= u;
				multi[j] /= v;
				ans[cur_id][i] = 0;
				ans[cur_id][j] = 0;
			}
		}
	}
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", x + i);
	}
	for(int i = 1; i <= n; i ++) {
		scanf("%d", y + i);
	}
	for(int i = 1; i <= n; i ++) {
		multi[i] = 1;
	}
	dfs(1);
	return 0;
}
