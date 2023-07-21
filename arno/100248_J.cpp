#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

vector<int> convert_4_base_integer(vector<int> base_10)
{
  vector<int> res;
  while (base_10.size())
  {
    int n = base_10.size(), s = 0;
    base_10.push_back(0);
    for (int i = n; i; i--)
    {
      s = (s *10 + base_10[i - 1]) % 4;
      base_10[i - 1] += base_10[i] % 4 * 10;
      base_10[i] /= 4;
    }

    base_10[0] /= 4;
    while (base_10.size() && !base_10.back())
    {
      base_10.pop_back();
    }

    res.push_back(s);
  }

  return res;
}

const int max_n = 1010;
char s[max_n];
pair<int, int> dynamic[max_n << 1][2];

void update(pair<int, int> &a, pair<int, int> &b, int c)
{
  if (!a.second || a.first > b.first + c)
  {
    a.second = b.second;
    a.first = b.first + c;
  }
  else if (a.first == b.first + c)
  {
    a.second = (a.second + b.second) % 1000000000;
  }
}

int main()
{
  vector<int> a;
  cin >> s;
  int n = strlen(s);
  for (int i = n - 1; i >= 0; i--)
  {
    a.push_back(s[i] - '0');
  }

  a = convert_4_base_integer(a);
  a.push_back(0);
  n = a.size();
  dynamic[0][0] = pair<int, int> (0, 1);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      if (dynamic[i][j].second)
      {
        int digit = a[i] + j;
        update(dynamic[i + 1][1], dynamic[i][j], 4 - digit);
        update(dynamic[i + 1][0], dynamic[i][j], digit);
      }
    }
  }

  cout << dynamic[n][0].second << endl;
  return 0;
}
