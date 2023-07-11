#include <bits/stdc++.h>
using namespace std;
using VI = vector<int>;

const int maxn = 1e5 + 10;
VI adj[maxn], st;
vector<VI> cycle;
int flag[maxn], dump[maxn];
set<pair<int,int>> mp;

void dfs(const int v, const int p) 
{
	flag[v] = 1;
	st.push_back(v);
	for (const int w : adj[v]) 
	{
		if (w == p) continue;
		if (dump[w]) continue;

		if (flag[w]) 
		{
			VI curcycle;
			int cp = w;
			for (int i = static_cast<int>(st.size()) - 1; i >= 0; --i) 
			{
				int t = st[i];
				mp.insert({cp, t});
				mp.insert({t, cp});
				curcycle.push_back(t);
				if (t == w)
					break;
				cp = t;
			}
			reverse(begin(curcycle), end(curcycle));
			for (int x : curcycle)
			{
				dump[x] = 1;
			}
			cycle.push_back(curcycle);
		}
		else 
		{
			dfs(w, v);
		}
	}
	st.pop_back();
}



int dp[maxn];
int DP[maxn];

void dfs_get(const int v) 
{
	flag[v] = 1;
	for (const int w : adj[v])
	{
		if (!flag[w]) 
		{
			dfs_get(w);
			if (mp.find({v, w}) == mp.end())
			{
				dp[v] = min(dp[v], DP[w]);
			}
			DP[v] = min(DP[v], DP[w]);
		}
	}
	DP[v] = min(DP[v], dp[v]);
}


int ans[maxn];

void dfs_final(int v) 
{
	flag[v] = 1;
	for (const int w : adj[v])
	if (!flag[w]) {
		dfs_final(w);
		if (mp.find({v, w}) == mp.end()) 
		{
			if (dump[w])
			{
				++ans[DP[w]];
			}
			else
			{
				++ans[dp[w]];
			}
		}
	}
}

int main()
{
	fill(begin(dp), end(dp), maxn - 1);
	fill(begin(DP), end(DP), maxn - 1);

	int n,m;
	cin >> n >> m;

	while (m--)  
	{
		int a,b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int k;
	cin >> k;

	for (int i = 0; i < k; ++i) 
	{
		int x;
		cin >> x;
		if (dp[x] > k)
			dp[x] = DP[x] = i;
	}

	dfs(1, 0);
	fill(begin(flag), end(flag), 0);
	dfs_get(1);

	for (const auto& vec : cycle) 
	{
		int k = (vec.size() + 1) / 2;
		multiset<int> ut;
		for (int i = 1; i < vec.size(); ++i) 
		{
			ut.insert(dp[vec[i]]);
			if (i >= k) 
			{
				ans[*ut.begin()] += 2;
				ut.erase(ut.find(dp[vec[i - k + 1]]));
			}
		}
	}

	fill(begin(flag), end(flag), 0);
	dfs_final(1);

	for (int i = 0; i < k; ++i)
	{
		printf("%d%c", ans[i], " \n"[i == k - 1]);
	}
	
	return 0;
}
