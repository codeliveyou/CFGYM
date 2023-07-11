#include<bits/stdc++.h>
using namespace std;
using INT = long long;

const INT mod = 1e6;
const INT N = 72000;

INT flag[N + 1];
INT sum_flag[2 * N + 1];

INT solve(INT x, INT y, INT d) {
	if(x == 0 || y == 0) {
		return 0;
	}
	if(x == 1) {
		return y;
	}
	if(x + y <= 2 * N && sum_flag[x + y] != -1) {
		return sum_flag[x + y];
	}
	if(d <= N && flag[d] != -1) {
		return flag[d];
	}
	
	INT lim = floor(sqrtl(y)) + 1;
	INT ans = ((x % mod) * (y % mod)) % mod;
	
	for(INT i = 2; i < lim; i ++) {
		ans -= solve(x / i, y / i, d * i);
	}
	ans %= mod;
	
	INT i = lim;
	INT nx, ny;
	
	while(i <= x) {
		nx = x / (x / i);
		ny = y / (y / i);
		ans -= solve(x / i, y / i, d * i) * (min(nx, ny) - i + 1);
		ans %= mod;
		i = min(nx, ny) + 1;
	}
	
	if(d <= N) {
		flag[d] = ans;
	}
	if(x + y <= 2 * N) {
		sum_flag[x + y] = ans;
	}
	return ans;
}

int main(){
	memset(flag, -1, sizeof flag);
	memset(sum_flag, -1, sizeof sum_flag);
	
	INT k, b;
	cin >> k >> b; b--;
	if(k >= b) {
		swap(k, b);
	}
	
	cout << (solve(k, b, 1) + mod) % mod << endl;
	
	return 0;
}
