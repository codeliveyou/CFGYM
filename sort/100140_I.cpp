#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to, cap, flow;
    Edge * rev;

    Edge() {}

    Edge(int to, int cap):
        to(to), cap(cap), flow(0), rev(NULL) {}
};

const int N = 120;
const int INF = 1e9;

int n;
int sou, tar;
vector < Edge * > e[N];
int dist[N];
int id[N];
int q[N];

void clear() {
    for (int i = 0; i < N; ++i) {
        for (Edge * ed: e[i]) {
            delete ed;
        }
        e[i].clear();
    }
}

void add_diedge(int from, int to, int cap) {
    Edge * a = new Edge(to, cap);
    Edge * b = new Edge(from, 0);
    a -> rev = b;
    b -> rev = a;
    e[from].push_back(a);
    e[to].push_back(b);
}

bool bfs() {
    fill(dist, dist + n, INF);
    dist[sou] = 0;
    int h = 0;
    int t = 0;
    q[t++] = sou;
    while (h < t && dist[tar] == INF) {
        int v = q[h++];
        for (Edge * ed: e[v]) {
            if (dist[ed -> to] == INF && (ed -> cap > ed -> flow)) {
                q[t++] = ed -> to;
                dist[ed -> to] = dist[v] + 1;
            }
        }
    }
    return dist[tar] < INF;
}

int dfs(int v, int flow) {
    if (v == tar || flow == 0) {
        return flow;
    }
    for (int & i = id[v]; i < (int) e[v].size(); ++i) {
        Edge * ed = e[v][i];
        if (dist[v] + 1 == dist[ed -> to] && (ed -> cap > ed -> flow)) {
            int now = dfs(ed -> to, min(flow, ed -> cap - ed -> flow));
            if (now > 0) {
                ed -> flow += now;
                ed -> rev -> flow -= now;
                return now;
            }
        }
    }
    return 0;
}

long long get_flow() {
    long long flow = 0;
    while (bfs()) {
        fill(id, id + n, 0);
        for (int now = 1; now;) {
            now = dfs(sou, INF);
            flow += now;
        }
    }
    return flow;
}

int cnt, k;
int capacity[N];
int good[N];

bool can(int mask) {
    clear();
    n = cnt + k + 2;
    sou = n - 1;
    tar = n - 2;
    for (int i = 0; i < k; ++i) {
        add_diedge(sou, i, 1);
    }
    for (int i = 0; i < k; ++i) {
        int here = mask & good[i];
        for (int j = 0; j < cnt; ++j) {
            if (((here >> j) & 1) == 1) {
                add_diedge(i, j + k, 1);
            }
        }
    }
    for (int i = 0; i < cnt; ++i) {
        if (((mask >> i) & 1) == 1) {
            add_diedge(i + k, tar, capacity[i]);
        }
    }
    return get_flow() == k;
}

int main() {
    scanf("%d%d", & cnt, & k);
    for (int i = 0; i < cnt; ++i) {
        scanf("%d", capacity + i);
    }
    for (int i = 0; i < k; ++i) {
        int t;
        scanf("%d", & t);
        for (int j = 0; j < t; ++j) {
            int x;
            scanf("%d", & x);
            good[i] |= 1 << (x - 1);
        }
    }
    if (!can((1 << cnt) - 1)) {
        puts("-1");
        return 0;
    }
    int ans = cnt;
    for (int mask = 1; mask < (1 << cnt) - 1; ++mask) {
        int now = __builtin_popcount(mask);
        if (now >= ans) {
            continue;
        }
        int sum = 0;
        for (int i = 0; i < cnt; ++i) {
            if (((mask >> i) & 1) == 1) {
                sum += capacity[i];
            }
        }
        bool ok = sum >= k;
        for (int i = 0; ok && i < k; ++i) {
            ok &= (good[i] & mask) != 0;
        }
        if (ok && can(mask)) {
            ans = now;
        }
    }
    printf("%d\n", ans);
    return 0;
}
