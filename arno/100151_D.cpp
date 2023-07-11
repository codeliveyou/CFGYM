#include<bits/stdc++.h>

using namespace std;

const int N = 2525;

int ans[N][N], vis[N][N];
char s[N << 2];
int st[N], sz;

void smin(int & a, const int & b)
{
	if(a > b)
	{
		a = b;
	}
}

int calc(int l,int r)
{
	if(vis[l][r])
	{
		return ans[l][r];
	}
	vis[l][r] = 1;
	if(l > r)
	{
		return 0;
	}
	ans[l][r] = 1e9;
	if(s[l] == '*' && s[r] == '*')
	{
		smin(ans[l][r], calc(l + 1, r));
		smin(ans[l][r], calc(l, r - 1));
	}
	else if(s[l] == '*')
	{
		if(s[r] <= 'Z')
		{
			smin(ans[l][r], calc(l, r - 1) + 1);
		}
		smin(ans[l][r], calc(l + 1, r));
	}
	else if(s[r]=='*')
	{
		if(s[l] >= 'a')
		{
			smin(ans[l][r], calc(l + 1, r) + 1);
		}
		smin(ans[l][r], calc(l, r - 1));
	}
	else if(s[l] == s[r] - 'A' + 'a')
	{
		smin(ans[l][r], calc(l + 1, r - 1));
	}
	for(int i = 1; i <= sz; i ++)
	{
		if(st[i] >= (s[st[i]] == '*' ? l + 1 : l) && st[i] < r)
		{
			smin(ans[l][r], calc(l, st[i]) + calc(s[st[i]] == '*' ? st[i] : st[i] + 1, r));
		}
	}
	return ans[l][r];
}

int main(){
	freopen("input.txt", "r", stdin);
#ifdef ONLINE_JUDGE
	freopen("output.txt","w",stdout);
#endif
	scanf("%s", s + 1);
	int n = 0, not_star = 0;
	for(int i = 1; s[i]; i ++)
	{
		if(s[i] == '*' || s[i] >= 'a') {
			s[++ n] = s[i];
		}
		else if(s[n] == '*' || s[n] <= 'Z')
		{
			s[++ n] = s[i];
		}
		else if(s[n] == s[i] + 'a' - 'A')
		{
			n --;
		}
		else
		{
			puts("-1");
			return 0;
		}
		if(s[i] != '*')
		{
			not_star ++;
		}
	}
	for(int i = 1; i <= n; i ++)
	{
		if(s[i] == '*' || i < n && s[i] <= 'Z' && s[i + 1] >= 'a')
		{
			st[++ sz] = i;
		}
	}
	int res = calc(1, n);
	if(res == 1e9)
	{
		puts("-1");
	}
	else
	{
		printf("%d\n",(calc(1, n) + not_star) >> 1);
	}
	return 0;
}
