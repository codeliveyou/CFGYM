#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
using namespace std;
using pii = pair<int, int> ;
typedef long long INT;

const INT inf = LLONG_MAX;
const int maxn = 1e3 + 10, maxm = 1e4 + 10;

int n, m, T;
INT dp[maxn][2 * maxn], tp[maxn][2 * maxn], mx[maxn];
vector<pii> edge[maxn];

void smax(INT &a, const INT &b)
{
  if (a < b)
  {
    a = b;
  }
}

int main()
{
  cin >> n >> m >> T;
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    edge[u].pb({ v, w });
    edge[v].pb({ u, w });
  }

  if (T == 0)
  {
    puts("0");
    return 0;
  }

  for (int v = 1; v <= n; v++)
  {
    for (int e = 0; e <= 2 * n; e++)
    {
      dp[v][e] = -inf;
    }
  }

  dp[1][0] = 0;
  for (int e = 1; e <= 2 * n; e++)
  {
    for (int v = 1; v <= n; v++)
    {
      for (pii p: edge[v])
      {
        int u = p.x;
        int w = p.y;
        if (dp[u][e - 1] != -inf)
        {
          smax(dp[v][e], dp[u][e - 1] + w);
        }
      }
    }
  }

  for (int v = 1; v <= n; v++)
  {
    for (int s = 0; s <= 2 * n; s++)
    {
      tp[v][s] = -inf;
    }
  }

  for (int v = 1; v <= n; v++)
  {
    for (int x = 1; x <= 2 *n / 2; x++)
    {
      if (dp[v][x] != -inf)
      {
        for (int y = x; y <= 2 *n - x; y++)
        {
          if (dp[v][y] != -inf)
          {
            smax(tp[v][x + y], dp[v][x] + dp[v][y]);
          }
        }
      }
    }
  }

  INT ans = -1;
  for (int v = 1; v <= n; v++)
  {
    for (pii p: edge[v])
    {
      smax(mx[v], p.y);
    }
  }

  for (int v = 1; v <= n; v++)
  {
    for (int s = T % 2; s <= min(T, 2 *n); s += 2)
    {
      if (tp[v][s] != -inf)
      {
        smax(ans, tp[v][s] + (T - s) *mx[v]);
      }
    }
  }

  cout << ans << "\n";
  return 0;
}
