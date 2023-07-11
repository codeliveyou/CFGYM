#include <bits/stdc++.h>
using namespace std;

const int N = 2020;

int n, m;
int need[N][N];
char s[N][N] ; 

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int ans;

void dfs(int x, int y) {
	ans ++;
	int xx, yy;
	need[x][y] = 0;
	for(int i = 0; i < 4; i ++) {
		xx = x + 2 * dx[i];
		yy = y + 2 * dy[i];
		if(need[xx][yy] && 0 <= xx && xx < n && 0 <= yy && yy < m && s[x + dx[i]][y + dy[i]] == '.') {
			need[xx][yy] --;
			if(need[xx][yy] == 1) {
				dfs(xx, yy);
			}
			else if(need[xx][yy] == 0) {
				ans ++;
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	n = 2 * n - 1;
	m = 2 * m - 1;
	for(int i = 0; i < n; i ++) {
		scanf("%s", s[i]);
	}
	for(int i = 1; i < n; i += 2) {
		for(int j = 1; j < m; j += 2) {
			need[i][j] = 4;
			for(int k = 0; k < 4; k ++) {
				if(s[i + dx[k]][j + dy[k]] != '.') {
					need[i][j] --;
				}
			}
		}
	}
	for(int i = 1; i < n; i += 2) {
		for(int j = 1; j < m; j += 2) {
			if(need[i][j] == 1) {
				dfs(i, j);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
