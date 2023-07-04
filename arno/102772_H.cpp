#include <bits/stdc++.h>

using namespace std;

const int max_n = 200020;
int person[max_n];
int cnt[max_n];
int msg[max_n];
int msg_end;
int teahers;
int director;

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	
	for (int i = 1; i <= n; ++ i)
	{
		scanf("%d", person + i);
	}
	
	vector<int> res;
	for (int i = 0, t, a, b, x, ans; i < q; ++ i)
	{
		scanf("%d", &t);
		msg[++ msg_end] = -1;
		if (t == 1) 
		{
			scanf("%d %d", &a, &b);
			if (person[a] == 2 && person[b] == 1) 
			{
				msg[msg_end] = 1;
				++ teahers;
				++ director;
			}
			else if (person[a] == 1 && person[b] == 2)
			{
				++ director;
				++ cnt[b];
			}
			else 
			{
				++ cnt[b];
			}
		}
		else if (t == 2) 
		{
			scanf("%d %d", &a, &x);
			if (person[a] == 1 && msg[x] == 1)
			{
				-- teahers;
			}
			else {
				-- cnt[a];
			}
		} else {
			scanf("%d", &a);
			ans = cnt[a];
			if (person[a] == 0)
			{
				ans += director;
			}
			if (person[a] == 1)
			{
				ans += teahers;
			}
			res.push_back(ans);
		}
	}
	for(auto r : res) cout << r << endl;
	return 0;
}
