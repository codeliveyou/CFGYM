#include <bits/stdc++.h>
using namespace std;

const int max_n = 1e3 + 10;
const int max_m = 5e5 + 10;

int a[max_n];
int b[max_n];
int L1[max_m];
int L2[max_m];

int main()
{
  int n, s, ans = 0;
  int sz1 = 1, sz2 = 0;

  cin >> n >> s;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i];
  }

  sort(a + 1, a + n + 1);

  L1[sz1] = a[1] + a[2];
  for (int i = 4; i <= n - 1; i++)
  {
    for (int j = i + 1; j <= n; j++)
    {
      L2[++sz2] = a[i] + a[j];
    }
  }

  sort(L2 + 1, L2 + sz2 + 1);
  for (int k = 3; k <= n - 2; sz1 += k - 1, sz2 -= n - k - 1, k++)
  {
    for (int i = 1, j = sz2; i <= sz1 && j >= 1;)
    {
      while (j != 0 && s - (L1[i] + a[k]) < L2[j])
      {
        j--;
      }

      int ii = i;
      while (ii <= sz1 && L1[ii] == L1[i])
      {
        ii++;
      }

      if (j != 0 && L1[i] + L2[j] + a[k] == s)
      {
        int jj = j;
        while (jj >= 1 && L2[jj] == L2[j])
        {
          jj--;
        }

        ans += (ii - i) *(j - jj);
        j = jj;
      }

      i = ii;
    }

    for (int i = 1; i < k; i++)
    {
      b[i] = a[i] + a[k];
    }

    for (int p = sz1 + (k - 1), i = sz1, j = k - 1; p >= 1;)
    {
      if (i >= 1 && j >= 1)
      {
        if (L1[i] > b[j])
        {
          while (i >= 1 && L1[i] > b[j])
          {
            L1[p--] = L1[i--];
          }
        }
        else
        {
          while (j >= 1 && L1[i] <= b[j])
          {
            L1[p--] = b[j--];
          }
        }
      }
      else
      {
        while (i >= 1)
        {
          L1[p--] = L1[i--];
        }

        while (j >= 1)
        {
          L1[p] = b[j--];
        }
      }
    }

    for (int i = n; i > k + 1; i--)
    {
      b[i - k - 1] = a[i] + a[k + 1];
    }

    for (int p = 1, i = 1, j = 1; p <= sz2 - (n - k - 1); p++)
    {
      while (i <= sz2 && j <= n - k - 1 && L2[i] == b[j])
      {
        i++;
        j++;
      }

      L2[p] = L2[i++];
    }
  }

  cout << ans << endl;
  return 0;
}
