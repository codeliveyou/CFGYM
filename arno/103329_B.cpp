#include <bits/stdc++.h>
using namespace std;
using INT = long long;

INT cp, cm, h0, a1, d1, n;
INT ans, rem;

void solve(INT h)
{
	if (cp * (h - 1) > h0) return;
	INT d0 = cp * (h - 1) * a1 < h0 ? 0 : a1 - (h0 - 1) / (cp * (h - 1));
	rem = n - d0;
	if (rem < 0) return;
	ans = max(ans, cp * h * max(1LL, rem - d1));
	auto check = [&](INT k)
	{
		k = max(0LL, min(h, k));
		ans = max(ans, cp * (h - k) + cm * k * (rem - k));
	};
	INT v = (cm * rem - cp) / cm / 2;
	check(v);
	check(v + 1);
}

INT solve()
{
	cin >> cp >> cm >> h0 >> a1 >> d1 >> n;
	ans = 0;
	solve(1);
	for (INT l = 1, r; l < h0; l = r + 1)
	{
		r = (h0 - 1) / ((h0 - 1) / l);
		solve(r / cp + 1);
	}
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while (T --)
	{
		cout << solve() << endl;
	}
	return 0;
}
