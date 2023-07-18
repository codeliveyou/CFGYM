#include <bits/stdc++.h>

using namespace std;
typedef long long INT;
typedef pair<int, int> II;
typedef pair<INT, II> III;

const int dx[] = { 0, 0, 1, -1 };

const int dy[] = { 1, -1, 0, 0 };

const int maxn = 3e5 + 10;
const INT INF = 1e18;

int n, m;
INT p, q;
char s[maxn];
string g[maxn];
vector<II> t[maxn];
vector<INT> w[maxn];
priority_queue<III, vector < III>, greater<III>> pq;

int main()
{
  cin >> n >> m >> p >> q;

  for (int x = 0; x < n; x++)
  {
    scanf("%s", s);
    g[x] = string(s);
  }

  for (int x = 0; x < n; x++)
  {
    t[x] = vector<II> (m, II(-1, -1));
    w[x] = vector<INT> (m, INF);
    for (int y = 0; y < m; y++)
    {
      if (g[x][y] != '#')
      {
        if (g[x][y] == '.')
        {
          w[x][y] = 0;
        }
        else
        {
          t[x][y] = { x, y
          };

          if (g[x][y] == 'L')
          {
            t[x][y].second++;
          }

          if (g[x][y] == 'R')
          {
            t[x][y].second--;
          }

          if (g[x][y] == 'U')
          {
            t[x][y].first++;
          }

          if (g[x][y] == 'D')
          {
            t[x][y].first--;
          }
        }
      }
    }
  }

  for (int x = 0; x < n; x++)
  {
    for (int y = 0; y < m; y++)
    {
      if (w[x][y] == 0)
      {
        pq.push({ w[x][y],
          {
            x, y
          } });
      }
    }
  }

  while (!pq.empty())
  {
	int i, j;
    INT ww;
    pair<int, int> tmp;
    tie(ww, tmp) = pq.top();
    tie(i, j) = tmp;
    pq.pop();
    if (w[i][j] != ww)
    {
      continue;
    }

    for (int z = 0; z < 4; z++)
    {
      int a = i + dx[z], b = j + dy[z];
      if (a < 0 || n <= a || b < 0 || m <= b || t[a][b] == II(-1, -1))
      {
        continue;
      }

      int aa, bb;
      tie(aa, bb) = t[a][b];

      INT w2 = ww + (abs(aa - i) == 1 ? p : q);

      if (w[aa][bb] > w2)
      {
        w[aa][bb] = w2;
        pq.push({ w[aa][bb],
          {
            aa, bb
          } });
      }
    }
  }

  INT ans = INF;
  for (int x = 0; x < n; x++)
  {
    for (int y = 0; y < m; y++)
    {
      if (x + 1 < n && t[x][y] != II(x + 1, y))
      {
        ans = min(ans, w[x][y] + w[x + 1][y]);
      }

      if (y + 1 < m && t[x][y] != II(x, y + 1))
      {
        ans = min(ans, w[x][y] + w[x][y + 1]);
      }
    }
  }

  if (ans == INF)
  {
    puts("-1");
  }
  else
  {
    cout << ans << endl;
  }

  return 0;
}
