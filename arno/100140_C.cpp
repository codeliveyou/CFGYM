#include <set>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdio>
#include <vector>
#include <string>
#include <math.h>
#include <cctype>
#include <bitset>
#include <numeric>
#include <cstring>
#include <cassert>
#include <sstream>
#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long LL;


void solve() {
	int n, k;
	cin >> n >> k;
	vector<pii> p(n);
	
	for (int i = 0; i < n; ++i) {
		cin >> p[i].first >> p[i].second;
	}
	
	sort(p.begin(), p.end());
	set<pii> sp(p.begin(), p.end());
	set<pii> op = sp;
	
	int X = p[0].first;
	cout << "L" << ' ' << p[0].first << endl;
	queue<pii> q;
	q.push(p[0]);
	
	while (sp.size() < k) {
		pii x = q.front(); q.pop();
		pii z = x;
		z.first = -(x.first - X + 1) + X;
		sp.insert(z);
		
		int dx[] = {-1, +1, 0, 0};
		int dy[] = {0, 0, -1, +1};
		
		for (int i = 0; i < 4; ++i) {
			z = x;
			z.first += dx[i];
			z.second += dy[i];
			if (op.count(z)) {
				op.erase(z);
				q.push(z);
			}
		}
	}
	
	for (set<pii>::iterator is = sp.begin(); is != sp.end(); ++is) {
		cout << is->first << ' ' << is->second << endl;
	}
}

int main() {
	int tcase;
	cin >> tcase;
	while(tcase --) {
		solve();
	}
	return 0;
}
