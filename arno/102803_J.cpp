#include<bits/stdc++.h>
using namespace std;

using INT = long long;

const int maxn = 1e5 + 7;

struct pr
{
	INT x, y;
	bool operator < (pr a) const
	{
		return a.x * y - a.y * x < 0;
	}
};

priority_queue<pr> que[maxn];

int integrate(int u, int t)
{
	if(que[u].size() < que[t].size()) 
	{
		swap(u, t);
	}
	while(!que[t].empty()) 
	{
		que[u].push(que[t].top());
		que[t].pop();
	}
	return u;
}

int n;
INT ans;
int f[maxn], p[maxn];
INT a[maxn], b[maxn];
vector<int> adj[maxn];

void dfs(int u)
{
	p[u] = u;
	for(int i = 0; i < adj[u].size(); i ++)
	{
		int x = adj[u][i];
		dfs(x);
		p[u] = integrate(p[u], p[x]);
	}
	if(u > 1)
	{
		INT x = a[u], y = b[u];
		u = p[u];
		while(!que[u].empty())
		{
			pr w = que[u].top();
			if(x * w.y > y * w.x)
			{
				ans += y * w.x;
				x += w.x;
				y += w.y;
				que[u].pop();
			}
			else
			{
				break;
			}
		}
		pr w;
		w.x = x;
		w.y = y;
		que[u].push(w);
	}
}

int main(){
	cin >> n;
	for(int i = 2; i <= n; i ++)
	{
		scanf("%d", f + i);
		adj[f[i]].push_back(i);
	}
	for(int i = 1; i <= n; i ++)
	{
		scanf("%I64d%I64d", a + i, b + i);
	}
	dfs(1);
	INT f = 0;
	int u = p[1];
	while(!que[u].empty())
	{
		pr w = que[u].top();
		ans += w.x * f;
		f += w.y;
		que[u].pop();
	}
	printf("%I64d\n", ans);
	return 0;
}
