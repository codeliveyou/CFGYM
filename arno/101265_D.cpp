#include <bits/stdc++.h>
using namespace std;

void solve()
{
	int h1, w1;
	cin >> h1 >> w1;
	vector<string> s;
	for (int y = 0; y < h1; ++ y)
	{
		string t;
		cin>>t;
		s.push_back(t);
	}
	
	int h2, w2;
	cin >> h2 >> w2;
	
	if (h1 * w2 != h2 * w1)
	{
		puts("Bad size");
		return;
	}
	if(h1 <= h2)
	{
		if(h2 % h1)
		{
			puts("Bad size");
			return;
		}
		int k = h2 / h1;
		for (int y = 0; y < h1; ++ y)
		{
			string u = "";
			for (int x = 0; x < w1; ++ x)
			{
				for (int j = 0; j < k; ++ j){
					u += s[y][x];
				}
			}
			for (int j = 0;j<k;++j)
			{
				cout << u << endl;
			}
		}
	}
	else
	{
		if (h1 % h2)
		{
			puts("Bad size");
			return;
		}
		int k = h1 / h2;
		for (int y = 0; y < h1; y += k)
		{
			for (int x = 0; x < w1; x += k) {
				for (int dy = 0; dy < k; ++ dy)
				{
					for (int dx = 0; dx < k; ++ dx)
					{
						if (s[y][x] != s[y + dy][x + dx])
						{
							puts("Bad image");
							return;
						}
					}
				}
			}
		}
		for (int y = 0; y < h1; y += k)
		{
			string u = "";
			for (int x = 0; x < w1; x += k) {
				u += s[y][x];
			}
			cout << u << endl;
		}
	}
}

int main() {
	solve();
	return 0;
}
