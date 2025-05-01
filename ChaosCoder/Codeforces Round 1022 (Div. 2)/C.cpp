#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int a[N], c[N];
bool b[N];
vector<int> v[N];

int main() 
{
    int T; cin >> T;
    while(T --) {
      int n; scanf("%d", &n);
      for(int i = 0; i < n; i ++) {
        scanf("%d", a + i);
      }
      n = unique(a, a + n) - a;
      for(int i = 0; i < n; i ++) {
        b[i] = false;
        c[i] = a[i];
      }
      sort(c, c + n);
      int m = unique(c, c + n) - c;
      for(int i = 0; i < n; i ++) {
        a[i] = lower_bound(c, c + m, a[i]) - c;
        v[a[i]].push_back(i);
      }
      int ans = 0;
      for(int i = m - 1; i >= 0; i --) {
        for(auto j : v[i]) {
          if(j > 0 && b[j - 1]) {
            b[j] = true;
            continue;
          }
          if(j + 1 < m && b[j + 1]) {
            b[j] = true;
            continue;
          }
          b[j] = true;
          ans ++;
        }
      }
      cout << ans << endl;
      for(int i = 0; i < m; i ++) {
        v[i].clear();
      }
    }
}