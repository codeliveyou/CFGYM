#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

const int N = 1e6 + 10;

int ch[N];
int hc[N];

int power(int a, long long b, int ans = 1) {
	for(; b; b >>= 1, a = 1ll * a * a % mod) {
		if(b & 1ll) {
			ans = 1ll * ans * a % mod;
		}
	}
	return ans;
}

int C(int n, int m) {
	if(m < 0 || n < m) {
		return 0;
	}
	return 1ll * ch[n] * hc[n - m] % mod * hc[m] % mod;
}

char s[N];

int main()
{
//	freopen("input.txt", "r", stdin);
	for(int i = ch[0] = 1; i < N; i ++) {
		ch[i] = 1ll * ch[i - 1] * i % mod;
	}
	hc[N - 1] = power(ch[N - 1], mod - 2);
	for(int i = N - 2; i >= 0; i --) {
		hc[i] = 1ll * (i + 1) * hc[i + 1] % mod;
	}
	
	int answer = 1;
	int k, n;
	long long l;
	cin >> k >> n >> l;
	scanf("%s", s);
	
	int rem = 0;
	for(int i = n - 1; i >= 0; i --) {
		if(s[i] == 'O') {
			rem ++;
		}
		else {
			answer = 1ll * answer * C(rem, k) % mod;
			rem -= k;
		}
	}
	
	cout << power(answer, l) << endl;
	
	
	return 0;
}
