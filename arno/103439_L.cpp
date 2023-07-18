#include <bits/stdc++.h>
using namespace std;
using BIGINT = __int128;
using INT = long long;
const int BIT = 1 << 11;

INT tot[40];

void insert(INT x)
{
  for (int i = 39; i >= 0; --i)
  {
    if ((x >> i) &1)
    {
      if (!tot[i])
      {
        tot[i] = x;
        return;
      }
      else
      {
        x ^= tot[i];
      }
    }
  }
}

INT _power(BIGINT a, INT b, INT P)
{
  BIGINT ret = 1;
  while (b)
  {
    if (b & 1)
    {
      ret = ret *a % P;
    }

    a = a *a % P;
    b >>= 1;
  }

  return ret;
}

int b[] = { 2, 5, 7, 37, 61 };

bool is_ok(INT x)
{
  for (auto &i: b)
  {
    if (x == i)
    {
      return 1;
    }
  }

  if (x % 2 == 0)
  {
    return 0;
  }

  INT d = x - 1;
  while (d % 2 == 0)
  {
    d /= 2;
  }

  for (auto &a: b)
  {
    INT t = d, y = _power(a, t, x);
    while (t != x - 1 && y != 1 && y != x - 1)
    {
      t <<= 1;
      y = BIGINT(y) *y % x;
    }

    if (y != x - 1 && t % 2 == 0) return 0;
  }

  return 1;
}

void add(INT L, INT R)
{
  if (R - L + 1 <= BIT)
  {
    for (INT i = L; i <= R; i++)
    {
      if (is_ok(i))
      {
        insert(i);
      }
    }

    return;
  }

  insert(L + 1);
  for (INT i = 2; i < R - L + 1; i <<= 1)
  {
    insert(i);
  }
}

void insert(INT L, INT R, INT ql, INT qr)
{
  if (L == ql && R == qr)
  {
    return add(L, R);
  }

  INT mid = (L + R) >> 1;
  if (qr <= mid)
  {
    insert(L, mid, ql, qr);
  }
  else if (ql > mid)
  {
    insert(mid + 1, R, ql, qr);
  }
  else
  {
    insert(L, mid, ql, mid);
    insert(mid + 1, R, mid + 1, qr);
  }
}

int main()
{
  int T;
  cin >> T;
  while (T--)
  {
    INT L, R;
    cin >> L >> R;
    memset(tot, 0, sizeof tot);
    insert(0, (1ll << 40) - 1, L, R);
    int ct = 0;
    for (int i = 0; i < 40; i++)
    {
      if (tot[i])
      {
        ++ct;
      }
    }

    cout << (1ll << ct) << endl;
  }

  return 0;
}
