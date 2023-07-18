#include<bits/stdc++.h>
using namespace std;

const int N = 55;

int n, m, p, ans;
int a[N], u[N], v[N];

void dfs(int x, int t) {
	if(x == 0) {
		ans += t;
		return;
	}
	if(a[u[x]] < a[v[x]]) {
		dfs(x - 1, t);
		swap(a[u[x]], a[v[x]]);
		dfs(x - 1, t);
		swap(a[u[x]], a[v[x]]);
	}
}

int solve() {
	scanf("%d %d %d", &n, &m, &p);
	ans = 0;
	for(int i = 1; i <= m; i ++) {
		scanf("%d %d", u + i, v + i);
		u[i]--, v[i]--;
	}
	for(int i = 0; i < n; i ++) {
		a[i] = i;
	}
	dfs(m, 1);
	for(int i = 0; i < n - 1; i ++) {
		swap(a[i], a[i + 1]);
		dfs(m, -1);
		swap(a[i], a[i + 1]);
	}
	for(int t = 0; t < n; t ++) {
		for(int i = 0; i < n; i ++) {
			if(i != t) {
				int c = 0;
				for(int j = 0; j < n; j ++) {
					if(j == i) {
						a[j] = t;
					}
					else {
						if(c == t) {
							c ++;
						}
						a[j] = c ++;
					}
				}
				dfs(m, 1);
			}
		}
	}
	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T --) {
		cout << solve() << endl;
	}
	return 0;
}
