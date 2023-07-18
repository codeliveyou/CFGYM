#include <bits/stdc++.h>
using namespace std;

int dp[105][105][75][75];
char s[105][105];

void smax(int & a, int b) {
	if(a < b) {
		a = b;
	}
}

int main(){
	int n, m, ans = 0;
	cin >> n >> m;
	for(int i = 0; i < n; i ++)
	{
		scanf("%s", s[i]);
	}
	
	memset(dp, -1, sizeof dp);
	
	dp[0][1][0][0] = 0, dp[1][0][0][0]=0;
	for(int i = 1, x, y, z; i <= n; i ++)
	{
		for(int j = 1; j <= m; j ++)
		{
			for(int k = 0; k < 70; k ++)
			{
				for(int l = 0; l < 70; l ++)
				{
					int x = k, y = l, z = 0;
					if(s[i - 1][j - 1] == '>')
					{
						x --;
					}
					else if(s[i - 1][j - 1] == '|')
					{
						y--;
					}
					else
					{
						z++;
					}
					x = max(x, 0);
					y = max(y, 0);
					if(dp[i - 1][j][x][y] != -1)
					{
						smax(dp[i][j][k][l], dp[i - 1][j][x][y] + z);
					}
					if(dp[i][j - 1][x][y] != -1)
					{
						smax(dp[i][j][k][l], dp[i][j - 1][x][y] + z);
					}
					ans = max(min(min(k, l), dp[i][j][k][l]), ans);
				}
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
