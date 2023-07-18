#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int m_pow(int a, int b)
{
  int ans = 1;
  for (; b; b >>= 1, a = 1ll *a *a % MOD)
  {
    if (b & 1)
    {
      ans = 1ll *ans *a % MOD;
    }
  }

  return ans;
}

int n;
int implement(int p = 1, int k = 1, int r = 1)
{
  if (p > n)
  {
    return 0;
  }

  if (p == n)
  {
    return r;
  }

  return max(implement(p + 1, k + 1, r + 1), implement(p + k, k, r *k));
}

int solve()
{
  if (n <= 25)
  {
    return implement();
  }

  if (n % 3 == 0)
  {
    return m_pow(3, n / 3);
  }

  if (n % 3 == 1)
  {
    return m_pow(3, n / 3) + 1;
  }

  if (n % 3 == 2)
  {
    return m_pow(3, n / 3 - 1) *5LL % MOD;
  }
}

int main()
{
  cin >> n;
  cout << solve() << endl;
  return 0;
}
