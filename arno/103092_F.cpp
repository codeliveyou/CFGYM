#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
using namespace std;
using pii = pair <int, int>;

const int N = 5222;

int n, bit[N];
void add(int u) 
{
	for(u ++; u <= n; u += u & -u) bit[u] ++;
}

short get(int u) 
{
	int ans = 0;
	for(u ++; u > 0; u -= u & -u) ans += bit[u];
	return ans;
}

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
int dp[N][N][4];
bool a[N][N];
int A[N], B[N];
vector<int> qq[N];

int main() {
	cin >> n;
	for(int i = 1; i <= n; i ++) 
	{
		for(int j = 1; j <= n / 4; j ++) 
		{
			char x; cin >> x;
			int b = -1;
			if('0' <= x && x <= '9') b = x - '0';
			else b = x - 'A' + 10;
			for(int k = 1; k <= 4; k ++) 
			{
				a[i][(j - 1) * 4 + k] = ((b >> (3 - (k - 1))) & 1);
			}
		}
	}
	for(int j = 1; j <= n; j ++) 
	{
		for(int i = 1; i <= n; i ++) 
		{
			if(a[i][j]) 
			{
				dp[i][j][2] = dp[i + 1][j - 1][2] + 1;
				dp[i][j][3] = dp[i - 1][j - 1][3] + 1;
			}
		}
	}
	for(int j = n; j > 0; j --) 
	{
		for(int i = 1; i <= n; i ++) 
		{
			if(a[i][j]) 
			{
				dp[i][j][0] = dp[i - 1][j + 1][0] + 1;
				dp[i][j][1] = dp[i + 1][j + 1][1] + 1;
			}
		}
	}
	long long ans = 0;
	for(int i = 1; i <= n; i ++) 
	{
		for(int j = 1; j <= n; j ++) 
		{
			A[j] = min(dp[i][j][0], dp[i][j][1]);
			B[j] = min(dp[i][j][2], dp[i][j][3]);
		}
		for(int x = 0; x < 2; x ++) 
		{
			vector <pii> ary;
			memset(bit, 0, sizeof bit);
			for(int k = 1; k <= n; k ++) 
			{
				if(k % 2 == x) 
				{
					ary.pb({A[k], B[k]});
				}
			}
			for(int j = 0; j < ary.size(); ++j) 
			{
				int l = j + 1, r = min((int)ary.size(), j + ary[j].x) - 1;
				if(l <= r) ans -= l, qq[r].pb(j);
			}
			for(int j = 0; j < ary.size(); ++j) 
			{
				add(max(0, j - ary[j].y + 1));
				for(auto it : qq[j]) ans += get(it);
				qq[j].clear();
			}
		}
	}
	cout << ans << endl;
	return 0;
}
