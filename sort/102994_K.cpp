#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

using pii = pair<int, int>;
using pi3 = pair<pii, int>;

const int M = 200;
const int N = 3e5 + 10;

int n, m, st[N], en[N], ed, deep[N];
vector <int> edge[N], thing[N], height[N];

struct tree {
	int x, y, tp;
	vector <pi3> V;
	vector <int> vx, T;
	void init(int _x, int _y) {
		x = _x, y = _y;
		V.clear(), vx.clear(), T.clear();
		tp = 0;
	}
	void update(int l, int r, int v) {
		l = (int)(lower_bound(vx.begin(), vx.end(), l) - vx.begin());
		r = (int)(upper_bound(vx.begin(), vx.end(), r) - vx.begin());
		for(int a=r;a;a-=(a&-a)) T[a] += v;
		for(int a=l;a;a-=(a&-a)) T[a] -= v;
	}
	int read(int a) {
		a = (int)(lower_bound(vx.begin(), vx.end(), a) - vx.begin() + 1);
		int res = 0;
		for(int i=a;i<=vx.size();i+=(i&-i)) res += T[i];
		return res;
	}
	void resolve() {
		for(int d=y;d<=n;d+=x) vx.insert(vx.end(), height[d].begin(), height[d].end());
		sort(vx.begin(), vx.end());
		T.resize(vx.size() + 1);
		for(auto v : V) {
			update(v.x.x, v.x.y, v.y);
		}
		tp = 1;
	}
	void add_seg(int l, int r, int v) {
		if(tp == 0) {
			V.push_back({{l, r}, v});
			if(V.size() >= M / 5) {
				resolve();
			}
		}
		else {
			update(l, r, v);
		}
	}
	int get_v(int a) {
		int res = 0;
		if(tp == 0) {
			for(auto v : V) {
				if(v.x.x <= a && a <= v.x.y) res += v.y;
			}
			return res;
		}
		return read(a);
	}
} Tree[M+1][M+1];

void add_th(int id, int l, int r, int v) {
	l = (int)(lower_bound(height[id].begin(), height[id].end(), l) - height[id].begin());
	r = (int)(upper_bound(height[id].begin(), height[id].end(), r) - height[id].begin());
	for(int a=r;a;a-=(a&-a)) thing[id][a] += v;
	for(int a=l;a;a-=(a&-a)) thing[id][a] -= v;
}

int read_th(int id, int x) {
	x = (int)(lower_bound(height[id].begin(), height[id].end(), x) - height[id].begin() + 1);
	int res = 0;
	for(int i=x;i<=height[id].size();i+=(i&-i)) res += thing[id][i];
	return res;
}

void pdfs(int x) {
	st[x] = ++ed;
	height[deep[x]].push_back(st[x]);
	for(int e : edge[x]) {
		pdfs(e);
	}
	en[x] = ed;
}

void solve() {
	for(int x=1;x<=M;x++) for(int y=0;y<x;y++) {
		Tree[x][y].init(x, y);
	}
	scanf("%d%d", &n, &m);
	deep[1] = 1;
	for(int i=2;i<=n;i++) {
		int x; scanf("%d", &x);
		edge[x].push_back(i);
		deep[i] = deep[x] + 1;
	}
	ed = 0;
	pdfs(1);
	for(int i=1;i<=n;i++) {
		sort(height[i].begin(), height[i].end());
		thing[i].resize(height[i].size() + 1);
	}
	for(int mm = 0; mm < m; mm ++) {
		int cmd; scanf("%d", &cmd);
		if(cmd == 1) {
			int a, x, y, z;
			scanf("%d%d%d%d", &a, &x, &y, &z);
			int l = st[a], r = en[a];
			if(x > M) {
				for(int v=deep[a]+y;v<=n;v+=x) {
					add_th(v, l, r, z);
				}
			}
			else {
				y = (deep[a] + y) % x;
				Tree[x][y].add_seg(l, r, z);
			}
		}
		else {
			int x; scanf("%d", &x);
			int res = read_th(deep[x], st[x]);
			for(int v=1;v<=M;v++) {
				res += Tree[v][deep[x] % v].get_v(st[x]);
			}
			printf("%d\n", res);
		}
	}

	for(int i=1;i<=n;i++) {
		edge[i].clear();
		thing[i].clear();
		height[i].clear();
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T --) {
		solve();
	}
	return 0;
}
