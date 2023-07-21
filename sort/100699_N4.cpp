#include <bits/stdc++.h>

using namespace std;

const int N = 111;

vector < int > adj[N];
int weight[N], sum[N], siz[N];

void dfs(int u) {
	sum[u] = weight[u];
	siz[u] = 1;
	for (auto v: adj[u]) {
		dfs(v);
		sum[u] += sum[v];
		siz[u] += siz[v];
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("inputdata.txt", "r", stdin);
	#endif
	int n;
	scanf("%d", & n);
	for (int i = 1; i <= n; i++) {
		int father;
		scanf("%d %d", & father, weight + i);
		adj[father].push_back(i);
	}
	dfs(1);
	double ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, (double) sum[i] / siz[i]);
	}
	printf("%.3lf\n", ans);
	return 0;
}
