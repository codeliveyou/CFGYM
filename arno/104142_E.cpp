#include "bits/stdc++.h"
using namespace std;
const int NN = 3001;
int a[NN], b[NN];
char s[NN];

int main() {
	int n, m;
	cin >> n >> m;
	long long ans = 0;
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", s);
		for(int j = 0; j < m; ++j)
		{
			if(s[j] == '.')
			{
				a[j] = 0;
			}
			else 
			{
				if(i > 0 && j > 0)
				{
					a[j] = min({a[j - 1], b[j], b[j - 1]}) + 1;
				}
				else 
				{
					a[j] = 1;
				}
			}
			ans += a[j];
		}
		for(int j = 0; j < m; ++j)
		{
			b[j] = a[j];
		}
	}
	cout << ans << endl;
	return 0;
}
