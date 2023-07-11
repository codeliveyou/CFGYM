#include<bits/stdc++.h>
using namespace std;
double solve() {
	double a, b, t, d, s;
	cin >> a >> b >> t >> d >> s;
	double ans = 0;
	double x = a * d, y = x * a / (b - a);
	if(x + y >= t || b <= a)
	{
		return 0;
	}
	do
	{
		ans ++;
		x = x + y;
		x = x + a * (x / b + s);
		y = x * a / (b - a);
	} while(x + y < t);
	return ans;
}
int main() {
	cout << solve() << endl;
	return 0;
}
