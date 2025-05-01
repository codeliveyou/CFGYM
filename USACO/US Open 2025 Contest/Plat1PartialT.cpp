#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;
using pi3 = pair<pii, int>;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t, m;
    cin >> t >> m;
    if (m == 1) {
        
        while (t--) {
            int n;
            cin >> n;
            vector<vector<int>> a(n, vector<int> (4));
            vector<vector<int>> adj(n);
            vector<int> deg(n, 0);
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 4; j++) {
                    cin >> a[i][j];
                    a[i][j] --;
                }
            }
            
            vector<vector<int>> st(n * 2 + 1);
            vector<vector<int>> ed(n * 2 + 1);
            set<pi3> seg;
            
            for(int i = 0; i < n; i ++) {
                st[a[i][0]].push_back(i);
                ed[a[i][2] + 1].push_back(i);
            }
            
            for(int i = 0; i <= n * 2; i ++) {
                for(auto j : ed[i]) {
                    seg.erase(seg.find(pi3(pii(a[j][1], a[j][3]), j)));
                }
                sort(st[i].begin(), st[i].end(), [&](int x, int y) {
                    return a[x][1] > a[y][1];
                });
                for(auto j : st[i]) {
                    auto p = seg.lower_bound(pi3(pii(a[j][1], 0), 0));
                    if(p != seg.end()) {
                        adj[j].push_back(p->second);
                        deg[p->second] ++;
                    }
                    seg.insert(pi3(pii(a[j][1], a[j][3]), j));
                }
                st[i].clear();
                ed[i].clear();
            }
            
            
            seg.clear();
            for(int i = 0; i < n; i ++) {
                st[a[i][1]].push_back(i);
                ed[a[i][3] + 1].push_back(i);
            }
            for(int i = 0; i <= n * 2; i ++) {
                for(auto j : ed[i]) {
                    seg.erase(seg.find(pi3(pii(a[j][0], a[j][2]), j)));
                }
                sort(st[i].begin(), st[i].end(), [&](int x, int y) {
                    return a[x][0] > a[y][0];
                });
                for(auto j : st[i]) {
                    auto p = seg.lower_bound(pi3(pii(a[j][0], 0), 0));
                    if(p != seg.end()) {
                        adj[j].push_back(p->second);
                        deg[p->second] ++;
                    }
                    seg.insert(pi3(pii(a[j][0], a[j][2]), j));
                }
                st[i].clear();
                ed[i].clear();
            }
            
            set<pii> q;
            
            for(int i = 0; i < n; i ++) {
                if(deg[i] == 0) {
                    q.insert({a[i][0], i});
                }
            }
            
            vector<int> answer;
            
            while(!q.empty()) {
                auto p = q.begin();
                int u = p->second;
                answer.push_back(u);
                q.erase(p);
                for(auto v : adj[u]) {
                    deg[v] --;
                    if(deg[v] == 0) {
                        q.insert({a[v][0], v});
                    }
                }
            }

            for (int it = 0; it < n; it++) {
                cout << answer[it] + 1 << " \n"[it + 1 == n];
            }
        }
    } else {
        while (t--) {
            int n;
            cin >> n;
            vector<vector<int>> a(n, vector<int> (4));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 4; j++) {
                    cin >> a[i][j];
                }
            }

            vector<int> f(2 * n + 1, 2 * n);

            auto upd = [&](int x, int y) {
                while (x <= 2 * n) {
                    f[x] = min(f[x], y);
                    x += x & -x;
                }
            };

            auto get = [&](int x) -> int {
                int res = 2 * n;
                while (x > 0) {
                    res = min(res, f[x]);
                    x -= x & -x;
                }
                return res;
            };

            vector<int> res(n, 1);
            for (int i = n - 1; i >= 0; i--) {
                if (get(a[i][2]) < a[i][3]) {
                    res[i] = 0;
                }
                upd(a[i][0], a[i][1]);
            }

            for (int x: res) {
                cout << x;
            }
            cout << "\n";
        }
    }
}
