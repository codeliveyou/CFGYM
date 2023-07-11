#include<bits/stdc++.h>
using namespace std;

const int max_n = 100;

int n, d[max_n], s[2], e[2], a[2][2], b[2][2];
bool flag[max_n];

void calc(int x, int y)
{
	fill(flag, flag + max_n, false);
	a[x][y] = b[x][y] = 0;
	int s0 = s[0], e0 = e[0];
	if (x)
	{
		swap(s0, e0);
	}
	for (int i = s0; i != e0; i = i % n + 1)
	{
		flag[i] = true;
		a[x][y] += d[i];
	}
	int s1 = s[1], e1 = e[1];
	if (y)
	{
		swap(s1, e1);
	}
	for (int i = s1; i != e1; i = i % n + 1)
	{
		b[x][y] += d[i];
		if (flag[i])
		{
			b[x][y] += d[i] + d[i];
			a[x][y] += d[i] + d[i];
		}
	}
}

pair<double, double> solve()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i)
	{
		scanf("%d", d + i);
	}
	for (int i = 0; i < 2; ++ i)
	{
		scanf("%d%d", s + i, e + i);
	}
	for (int x = 0; x < 2; ++ x)
	{
		for (int y = 0; y < 2; ++y)
		{
			calc(x, y);
		}
	}
	int b0 = a[1][1] - a[0][1];
	int k0 = b0 + a[0][0] - a[1][0];
	int b1 = b[1][1] - b[1][0];
	int k1 = b1 + b[0][0] - b[0][1];
	double q = 1.0 * b0 / k0;
	double p = 1.0 * b1 / k1;
	if(q < 0 || q > 1)
	{
		if(-b0 > 0)
		{
			p = 0;
			q = -b1 > 0 ? 0 : 1;
		}
		else
		{
			p = 1;
			q = k1 - b1 > 0 ? 0 : 1;
		}
	}
	if(p < 0 || p > 1)
	{
		if(-b1 > 0)
		{
			q = 0;
			p = -b0 > 0 ? 0 : 1;
		}
		else
		{
			q = 1;
			p = k0 - b0 > 0 ? 0 : 1;
		}
	}
	return
	{
		p * q * a[0][0] + (1 - p) * q * a[1][0] + p * (1 - q) * a[0][1] + (1 - p) * (1 - q) * a[1][1],
		p * q * b[0][0] + (1 - p) * q * b[1][0] + p * (1 - q) * b[0][1] + (1 - p) * (1 - q) * b[1][1]
	};
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T --)
	{
		auto ans = solve();
		printf("%.12f %.12f\n", ans.first, ans.second);
	}
	return 0;
}

//1
//5
//8 22 47 25 13
//3 5 3 1
//
//72.000000000000 30.000000000000
