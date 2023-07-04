#include <bits/stdc++.h>
using namespace std;

int n;
int r[12], c[12];
int ct[12];
int p[12][12];
int num[12];
int ok = 0;

set<int> st;

void rec(int x) {
    if (ok)
        return;
    if (x == n + 1) {
         for (int i = 1; i <= n; i++) {
             for (int j = 1; j <= n; j++) {
                 cout << p[i][j] << ' ';
             }
             cout << endl;
         }
         ok = 1;
         return;
    }

    for (int k = 1; k * k <= r[x]; k++) {
        if (r[x] % k)
            continue;
        int a = k, b = r[x] / k;
        if (st.find(a) != st.end() || st.find(b) != st.end())
            continue;
        if (a == b)
            continue;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j)
                    continue;
                if (num[i] == 2 || num[j] == 2)
                    continue;
                if (num[i] == 1 && ct[i] * a != c[i])
                    continue;
                if (num[j] == 1 && ct[j] * b != c[j])
                    continue;
                if (num[i] == 0 && c[i] % a)
                    continue;
                if (num[j] == 0 && c[j] % b)
                    continue;

                st.insert(a), st.insert(b);
                num[i]++, num[j]++;
                ct[i] *= a, ct[j] *= b;
                p[x][i] = a, p[x][j] = b;

                rec(x + 1);

                ct[i] /= a, ct[j] /= b;
                num[i]--, num[j]--;
                p[x][i] = 0, p[x][j] = 0;
                st.erase(a), st.erase(b);
            }
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> c[i], ct[i] = 1;
    for (int i = 1; i <= n; i++)
        cin >> r[i];
    rec(1);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(NULL), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed), cout.precision(20);
    solve();
    return 0;
}
