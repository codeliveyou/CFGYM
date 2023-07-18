#include <bits/stdc++.h>

using namespace std;

const int N = 4e4 + 10;

int n, m, t, _st[N], _ed[N], _wei[N], _eg[N], _cnt[N];

struct cmp {
	bool operator()(int i, int j) {
		if(_wei[i] != _wei[j]) {
			return _wei[i] < _wei[j];
		}
		return i < j;
	}
};

using Set = set < int, cmp > ;

struct {
	int f[N], p;
	void init() {
		++p;
	}
	bool get(int i) {
		return f[i] == p;
	}
	bool set(int i) {
		f[i] = p;
	}
}
vst;

struct dsu {
	int f[N], p, par[N];
	void init() {
		++p;
	}
	int Find(int x) {
		prop(x);
		return par[x] == x ? x : par[x] = Find(par[x]);
	}
	bool Union(int x, int y) {
		x = Find(x), y = Find(y);
		if (x == y) return false;
		par[x] = y;
		return true;
	}
	void prop(int x) {
		if (f[x] == p) return;
		f[x] = p;
		par[x] = x;
	}
}
UF, _UF_;

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d", & n, & m);
	Set st;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", _st + i, _ed + i, _wei + i);
		st.insert(i);
	}
	scanf("%d", & t);
	for (int i = 1; i <= t; i++) {
		scanf("%d %d", _eg + i, _cnt + i);
	}

	for (int l = 1, b = sqrt(n) + 1; l <= t; l += b) {
		int r = min(l + b - 1, t);
		vst.init();
		UF.init();

		Set sm;
		for (int i = l; i <= r; i++) {
			vst.set(_eg[i]);
			UF.Union(_st[_eg[i]], _ed[_eg[i]]);
			sm.insert(_eg[i]);
		}

		int id[N], cnt = 0;
		_UF_.init();
		for (int i: st) {
			if (!vst.get(i) && _UF_.Union(_st[i], _ed[i])) {
				id[++cnt] = i;
			}
		}

		_UF_.init();
		int tree = 0;
		for (int i = 1; i <= cnt; i++) {
			if (UF.Union(_st[id[i]], _ed[id[i]])) {
				_UF_.Union(_st[id[i]], _ed[id[i]]);
				tree += _wei[id[i]];
			} else {
				sm.insert(id[i]);
			}
		}

		for (int i = l; i <= r; i++) {
			st.erase(_eg[i]);
			sm.erase(_eg[i]);
			_wei[_eg[i]] = _cnt[i];
			st.insert(_eg[i]);
			sm.insert(_eg[i]);

			UF.init();
			int res = 0;
			for (int e: sm) {
				if (UF.Union(_UF_.Find(_st[e]), _UF_.Find(_ed[e]))) {
					res += _wei[e];
				}
			}
			printf("%d\n", tree + res);
		}
	}
	return 0;
}
