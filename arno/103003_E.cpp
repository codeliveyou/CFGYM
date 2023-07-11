#pragma GCC target("avx2")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

void gi(int & a, int & b) {
	gi(a), gi(b);
}

const int N = 1e5 + 10;

pii ed[N * 2];
int nex_forw[N * 2], be_forw[N];
int indeg[N], tp[N];
int n, m, q;
constexpr int BS = 8;
uint64_t dp[N][BS];
ll sm[N][BS];
int ql[N * 10], qr[N * 10];
ll qans[N * 10];
struct opty { int i, gx; };
vector<opty> offl[(N >> 6) + 10];

void init(int bl, int br) {
	int id = (bl >> 6) & (BS - 1);
	if(!id) {
		for(int i = n - 1; i >= 0; i --) {
			int u = tp[i];
			dp[u][0] = dp[u][0+1] = dp[u][0+2] = dp[u][0+3] = 0;
			dp[u][4] = dp[u][4+1] = dp[u][4+2] = dp[u][4+3] = 0;
			if((bl <= u) && (u < (bl + BS * 64))) {
				dp[u][(u - bl) >> 6] |= (1ull << ((u - bl) & 63));
			}
			int _L = be_forw[u], _R = be_forw[u+1];
			uint64_t *targ = dp[u];
			for(int i = _L; i < _R; i ++) {
				uint64_t *src = dp[nex_forw[i]];
				targ[0] |= src[0];
				targ[0+1] |= src[0+1];
				targ[0+2] |= src[0+2];
				targ[0+3] |= src[0+3];
				
				targ[4] |= src[4];
				targ[4+1] |= src[4+1];
				targ[4+2] |= src[4+2];
				targ[4+3] |= src[4+3];
			}
		}
		static int ps[BS];
		ps[0] = ps[0+1] = ps[0+2] = ps[0+3] = 0;
		ps[4] = ps[4+1] = ps[4+2] = ps[4+3] = 0;
		for(int i=n-1; i>=0; i--) {
			ps[0] += __builtin_popcountll(dp[i][0]);
			ps[0+1] += __builtin_popcountll(dp[i][0+1]);
			ps[0+2] += __builtin_popcountll(dp[i][0+2]);
			ps[0+3] += __builtin_popcountll(dp[i][0+3]);
			
			ps[4] += __builtin_popcountll(dp[i][4]);
			ps[4+1] += __builtin_popcountll(dp[i][4+1]);
			ps[4+2] += __builtin_popcountll(dp[i][4+2]);
			ps[4+3] += __builtin_popcountll(dp[i][4+3]);
			
			sm[i][0] = sm[i][(0+BS-1)%BS] + ps[0];
			sm[i][0+1] = sm[i][0] + ps[0+1];
			sm[i][0+2] = sm[i][0+1] + ps[0+2];
			sm[i][0+3] = sm[i][0+2] + ps[0+3];
			
			sm[i][4] = sm[i][(4+BS-1)%BS] + ps[4];
			sm[i][4+1] = sm[i][4] + ps[4+1];
			sm[i][4+2] = sm[i][4+1] + ps[4+2];
			sm[i][4+3] = sm[i][4+2] + ps[4+3];
		}
	}
}

void put(int tec) {
	int pt;
	sort(ed, ed+tec);
	for(int i = 0; i < tec; i ++) {
		indeg[ed[i].second]++;
	}
	pt = 0;
	for(int i = 0; i < n; i ++) {
		be_forw[i] = pt;
		while(pt != tec && ed[pt].first == i) {
			nex_forw[pt] = ed[pt].second;
			pt++;
		}
	}
	be_forw[n] = pt;
	queue<int> q;
	for(int i = 0; i < n; i ++) {
		if(!indeg[i]) {
			q.push(i);
		}
	}
	int idx = 0;
	while(!q.empty()) {
		int v = (tp[idx++] = q.front()); q.pop();
		int _L = be_forw[v], _R = be_forw[v+1];
		for(int i = _L; i < _R; i ++) {
			if(!(--indeg[nex_forw[i]])) {
				q.push(nex_forw[i]);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
//	freopen("input.txt", "r", stdin);
	gi(n, m);
//	scanf("%d %d", &n, &m);
	
	int tec = 0;
	for(int i = 1; i < n; i ++) {
		int p;
		gi(p);
//		scanf("%d", &p);
		p--;
		ed[tec++] = {p, i};
	}
	for(int i = 0; i < m; i ++) {
		int u, v;
		gi(u, v);
//		scanf("%d %d", &u, &v);
		ed[tec++] = {--u, --v};
	}
	put(tec);
	gi(q);
//	scanf("%d", &q);
	for(int i = 0; i < q; i ++) {
		gi(ql[i], qr[i]);
//		scanf("%d %d", ql + i, qr + i);
		ql[i]--;
		if((ql[i] >> 6) == ((qr[i]) >> 6)) {
			offl[ql[i] >> 6].push_back({i, 0});
			continue;
		}
		int bl = ql[i] + ((ql[i] & 63) ? (64 - (ql[i] & 63)) : 0);
		int br = qr[i] - (qr[i] & 63);
		bl >>= 6; br >>= 6;
		if(ql[i] != (bl << 6)) {
			offl[ql[i] >> 6].push_back({i, 0});
		}
		if(qr[i] != (br << 6)) {
			offl[(qr[i] - 1) >> 6].push_back({i, 0});
		}
		if(bl != br) {
			if(bl) offl[bl - 1].push_back({i, -1});
			offl[br - 1].push_back({i, 1});
		}
	}
	int Bl = 0, cur = 0;
	while(Bl != n) {
		int Br = min(Bl + 64, n);
		init(Bl, Br);
		int id = cur & (BS - 1);
		for(const opty& pog : offl[cur]) {
			int pl = ql[pog.i], pr = qr[pog.i];
			if(pog.gx == 1) {
				qans[pog.i] += sm[pl][id] - sm[pr][id];
			}
			if(pog.gx == -1) {
				qans[pog.i] -= sm[pl][id] - sm[pr][id];
			}
			if(pog.gx == 0) {
				int nql = max(pl, Bl), nqr = min(pr, Br), tmp = 0;
				uint64_t mask = ((1ull << (nqr - nql)) - 1) << (nql - Bl);
				if((pl >> 6) == (pr >> 6)) {
					for(int i = pl; i < pr; i ++) {
						tmp += __builtin_popcountll(dp[i][id] & mask);
					}
				}
				else {
					int bl = pl + ((pl & 63) ? (64 - (pl & 63)) : 0);
					int br = pr - (pr & 63);
					for(int i = pl; i < bl; i ++) {
						tmp += __builtin_popcountll(dp[i][id] & mask);
					}
					for(int i = br; i < pr; i ++) {
						tmp += __builtin_popcountll(dp[i][id] & mask);
					}
				}
				qans[pog.i] += tmp;
			}
		}
		Bl = Br;
		cur++;
	}
	for(int i = 0; i < tec; i ++) {
		swap(ed[i].first, ed[i].second);
	}
	put(tec);
	memset(sm, 0, sizeof sm);
	Bl = cur = 0;
	while(Bl != n) {
		int Br = min(Bl + 64, n);
		init(Bl, Br);
		int id = cur & (BS - 1);
		for(const opty& pog : offl[cur]) {
			int pl = ql[pog.i], pr = qr[pog.i];
			int bl = pl + ((pl & 63) ? (64 - (pl & 63)) : 0);
			int br = pr - (pr & 63);
			if(pog.gx == 1) {
				qans[pog.i] += sm[pl][id] - sm[bl][id] + sm[br][id] - sm[pr][id];
			}
			if(pog.gx == -1) {
				qans[pog.i] -= sm[pl][id] - sm[bl][id] + sm[br][id] - sm[pr][id];
			}
		}
		Bl = Br;
		cur++;
	}
	for(int i = 0; i < q; i ++) {
		print(qans[i]), pc('\n');
//		printf("%I64d\n", qans[i]);
	}
	return 0;
}
