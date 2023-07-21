#include <bits/stdc++.h>
using namespace std;

const int max_n = 55;
const double eps = 1e-7;

int w, h, n;
int x[max_n], y[max_n], r[max_n];
double R;

bool is_in(double x1, double y1, int id)
{
  return (x1 - x[id]) *(x1 - x[id]) + (y1 - y[id]) *(y1 - y[id]) < (r[id] + R) *(r[id] + R) + eps;
}

bool cover_wall(double x1, double y1, double x2, double y2)
{
  if (max(x2 - x1, y2 - y1) < eps)
  {
    return false;
  }

  for (int i = 0; i < n; ++i)
  {
    if (is_in(x1, y1, i) && is_in(x1, y2, i) && is_in(x2, y1, i) && is_in(x2, y2, i))
    {
      return true;
    }
  }

  if (!cover_wall(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2))
  {
    return false;
  }

  if (!cover_wall((x1 + x2) / 2, y1, x2, (y1 + y2) / 2))
  {
    return false;
  }

  if (!cover_wall(x1, (y1 + y2) / 2, (x1 + x2) / 2, y2))
  {
    return false;
  }

  if (!cover_wall((x1 + x2) / 2, (y1 + y2) / 2, x2, y2))
  {
    return false;
  }

  return true;
}

void solve()
{
  cin >> w >> h >> n;
  for (int i = 0; i < n; ++i)
  {
    cin >> x[i] >> y[i] >> r[i];
  }

  double st = 0;
  double ed = (double) min(w, h) / 2;
  for (int i = 0; i < 60; ++i)
  {
    R = (st + ed) / 2;
    if (cover_wall(R, R, w - R, h - R))
    {
      ed = R;
    }
    else
    {
      st = R;
    }
  }

  cout << fixed << setprecision(15) << st << endl;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tcase;
  cin >> tcase;
  for (int i = 0; i < tcase; ++i)
  {
    solve();
  }

  return 0;
}
