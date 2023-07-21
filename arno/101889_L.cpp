#include <bits/stdc++.h>
using namespace std;

int input()
{
  char r;
  bool start = false, neg = false;
  int ret = 0;
  while (true)
  {
    r = getchar();
    if ((r - '0'<0 || r - '0' > 9) && r != '-' && !start)
    {
      continue;
    }

    if ((r - '0'<0 || r - '0' > 9) && r != '-' && start)
    {
      break;
    }

    if (start) ret *= 10;
    start = true;
    if (r == '-') neg = true;
    else ret += r - '0';
  }

  if (!neg)
    return ret;
  else
    return -ret;
}

char buff[50];

void output(int d)
{
  if (!d)
  {
    putchar('0');
    putchar('\n');
    return;
  }

  if (d < 0)
  {
    putchar('-');
    d = -d;
  }

  char *x = buff;
  while (d)
  {
    *x = '0' + d % 10;
    x++;
    d /= 10;
  }

  do {
    x--;
    putchar(*x);
  }

  while (x != buff);
  putchar('\n');
}

const int max_n = 1e5 + 10;

int a[max_n][2], sum_a[max_n][2];
int p[max_n][2], q[max_n][2];

int main()
{
  freopen("in1.txt", "r", stdin);
  freopen("out1.txt", "w", stdout);

  int n;
  n = input();
  for (int j = 0; j < 2; j++)
  {
    p[1][j] = q[n][j] = n;
    for (int i = 1; i < n; i++)
    {
      a[i][j] = input();
      sum_a[i + 1][j] = sum_a[i][j] + a[i][j];
      if (a[i][j] == 1)
      {
        p[i + 1][j] = 0;
      }
      else
      {
        p[i + 1][j] = p[i][j] + 1;
      }
    }

    for (int i = n - 1; i; i--)
    {
      if (a[i][j] == 1)
      {
        q[i][j] = 0;
      }
      else
      {
        q[i][j] = q[i + 1][j] + 1;
      }
    }
  }

  int T;
  cin >> T;
  while (T--)
  {
    int start_x = input();
    int start_y = input();
    int end_x = input();
    int end_y = input();

    if (start_x > end_x)
    {
      swap(start_x, end_x);
    }

    if (start_y > end_y)
    {
      swap(start_y, end_y);
    }

    int res = sum_a[end_x][0] - sum_a[start_x][0] + sum_a[end_y][1] - sum_a[start_y][1];
    int delta_1 = abs(end_x - start_x - end_y + start_y) / 2, delta_2, u, v;

    int direction;
    if (end_x - start_x - end_y + start_y < 0)
    {
      u = start_x;
      v = end_x;
      direction = 0;
    }
    else
    {
      u = start_y;
      v = end_y;
      direction = 1;
    }

    if ((v - u) *5 > sum_a[v][direction] - sum_a[u][direction])
    {
      delta_2 = 0;
    }
    else
    {
      delta_2 = min(p[u][direction], q[v][direction]);
    }

    if (delta_2 < delta_1)
    {
      res += delta_2 * 10 + (delta_1 - delta_2) *2;
    }
    else
    {
      res += delta_1 * 10;
    }

    output(res);
  }

  return 0;
}
