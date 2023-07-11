#include <bits/stdc++.h>
using namespace std;

const int N=10000+19;
int root[N],sz[N];

int union_find(int x) {
	return root[x] == x ? x : root[x] = union_find(root[x]);
}

int main() {
    int T, cas = 0;
	cin >> T;
	while(T --) {
		int n, m;
        scanf("%d%d",&n, &m);
        for (int i = 1; i <= n; i ++) {
			root[i] = i;
			sz[i] = 0;
		}
        for (int i = 0; i < m; i ++) {
            int u, v;
			scanf("%d %d", &u, &v);
			int U = union_find(u);
			int V = union_find(v);
			if(U != V) {
				root[U] = V;
			}
        }
        for(int i = 1; i <= n; i ++) {
        	sz[union_find(i)] ++;
        }
        printf("Case #%d:\n", ++ cas);
        for(int i = 1; i <= n; i ++) {
			printf("%d%c", sz[root[i]] - 1, i == n ? '\n' : ' ');
		}
    }
    return 0;
}
