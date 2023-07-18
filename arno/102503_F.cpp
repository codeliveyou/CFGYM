#include <bits/stdc++.h>
using namespace std;
using INT = long long;
using pii = pair<int, int>;

const INT mod = 1000000007;
const INT invOf2 = 500000004;
const INT invOf6 = 166666668;

static inline INT S1(INT n)
{
  n %= mod;
  return n;
}

static inline INT S2(INT n)
{
  n %= mod;
  return n *(n + 1) % mod *invOf2 % mod;
}

static inline INT S3(INT n)
{
  n %= mod;
  return n *(n + 1) % mod *(2 *n + 1) % mod *invOf6 % mod;
}

static inline INT S4(INT n)
{
  INT tmp = S2(n);
  return tmp *tmp % mod;
}

INT query2(INT l, INT r, INT d, INT u, INT o, INT dx, INT dy)
{
  if (l > r || d > u)
  {
    return 0;
  }
  if (l == 1 && d == 1)
  {
    INT sq = min(r, u), ret = 0;
    ret = 8* S4(sq) + (2 *dx - 26) *S3(sq) + (25 + 2 *o - 3 *dx) *S2(sq) + (dx - 7 - o) *S1(sq);
    ret %= mod;
    if (r > u)
    {
      ret += (4 *(S3(r) - S3(sq)) + (dx - 12) *(S2(r) - S2(sq)) + (-dx + 8 + o) *(S1(r) - S1(sq))) % mod *sq % mod;
      ret += (S1(r) - S1(sq)) *sq % mod *(sq - 1) % mod *invOf2 % mod;
    }
    else if (u > r)
    {
      ret += (4 *(S3(u) - S3(sq)) + (dx - 10) *(S2(u) - S2(sq)) + (-dx + 6 + o) *(S1(u) - S1(sq))) % mod *sq % mod;
      ret -= (S1(u) - S1(sq)) *sq % mod *(sq - 1) % mod *invOf2 % mod;
    }

    return ret % mod;
  }

  return (query2(1, r, 1, u, o, dx, dy) - query2(1, l - 1, 1, u, o, dx, dy) -
    query2(1, r, 1, d - 1, o, dx, dy) + query2(1, l - 1, 1, d - 1, o, dx, dy)) % mod;
}

INT query3(INT l, INT r, INT d, INT u)
{
  if (d == 1)
  {
    return (query2(l, r, 1, 1, 4, 11, 0) + query2(l, r, 1, u - 1, 5, 11, 13)) % mod;
  }
  else
  {
    return query2(l, r, d - 1, u - 1, 5, 11, 13);
  }
}

INT get_sum(INT l, INT r, INT d, INT u)
{
  if (l > r || d > u)
  {
    return 0;
  }
  if (l <= 0 && r > 0)
  {
    return (get_sum(l, 0, d, u) + get_sum(1, r, d, u)) % mod;
  }
  if (d <= 0 && u > 0)
  {
    return (get_sum(l, r, d, 0) + get_sum(l, r, 1, u)) % mod;
  }
  if (l > 0 && d > 0)
  {
    return query2(l, r, d, u, 3, 9, 11);
  }
  else if (r <= 0 && d > 0)
  {
    return query3(d, u, -r + 1, -l + 1);
  }
  else if (r <= 0 && u <= 0)
  {
    return query2(-r + 1, -l + 1, -u + 1, -d + 1, 1, 5, 7);
  }
  else if (l > 0 && u <= 0)
  {
    return query2(-u + 1, -d + 1, l, r, 2, 7, 9);
  }
  else
  {
    return 0;
  }
}

pii get_position(INT a)
{
  INT c = sqrt(a);
  while (c * c > a)
  {
    --c;
  }
  if (c & 1) --c;
  while (c * c < a)
  {
    c += 2;
  }
  a -= (c - 2) *(c - 2) + 1;
  INT d = --c / 2;
  if (a < c)
  {
    return pii(0 - d, 0 + d - a);
  }
  a -= c;
  if (a < c)
  {
    return pii(1 - d + a, 0 - d);
  }
  a -= c;
  if (a < c)
  {
    return pii(1 + d, 1 - d + a);
  }
  a -= c;
  return pii(0 + d - a, 1 + d);
}

int main()
{
  int t;
  INT a, b, l, r, d, u;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%I64d %I64d", &a, &b);
    tie(l, d) = get_position(a);
    tie(r, u) = get_position(b);
    if (l > r)
    {
      swap(l, r);
    }
    if (d > u)
    {
      swap(d, u);
    }
    printf("%I64d\n", ((get_sum(l, r, d, u) + mod) % mod));
  }
  return 0;
}
