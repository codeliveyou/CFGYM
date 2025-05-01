#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
const int M = 100;

int n, q;

int a[N];
int c[N];

set<int> st[M];
unordered_set<int> mo;

int st_min[M], st_max[M];

void ers(int x) {
	if(c[x] < M) {
		st[c[x]].erase(x);
		if(!st[c[x]].empty()) {
			st_min[c[x]] = *st[c[x]].begin();
			st_max[c[x]] = *--st[c[x]].end();
		}
	}
	else {
		mo.erase(x);
	}
	c[x] --;
	if(c[x] < M) {
		st[c[x]].insert(x);
		st_min[c[x]] = *st[c[x]].begin();
		st_max[c[x]] = *--st[c[x]].end();
	}
	else {
		mo.insert(x);
	}
}

void add(int x) {
	if(c[x] < M) {
		st[c[x]].erase(x);
		if(!st[c[x]].empty()) {
			st_min[c[x]] = *st[c[x]].begin();
			st_max[c[x]] = *--st[c[x]].end();
		}
	}
	else {
		mo.erase(x);
	}
	c[x] ++;
	if(c[x] < M) {
		st[c[x]].insert(x);
		st_min[c[x]] = *st[c[x]].begin();
		st_max[c[x]] = *--st[c[x]].end();
	}
	else {
		mo.insert(x);
	}
}

int solve() {
	int mx = 0;
	if(mo.empty()) {
		for(int i = M - 1; i >= 0; i --) {
			if(!st[i].empty()) {
				mx = i;
				break;
			}
		}
	}
	else {
		for(auto i : mo) {
			mx = max(mx, c[i]);
		}
	}
	
	int answer = 0;
	
	for(auto x : mo) {
		for(auto y : mo) {
			if(x != y && c[x] + c[y] >= mx) {
				answer = max(answer, abs(x - y));
			}
		}
		for(int i = 1; i < M; i ++) {
			if(!st[i].empty() && c[x] + i >= mx) {
				answer = max(answer, abs(x - st_min[i]));
				answer = max(answer, abs(x - st_max[i]));
			}
		}
	}
	
	for(int i = 1; i < M; i ++) if(!st[i].empty()) {
		for(int j = max(i, mx - i); j < M; j ++) if(!st[j].empty()) {
			answer = max(answer, abs(st_max[i] - st_min[j]));
			answer = max(answer, abs(st_max[j] - st_min[i]));
		}
	}
	
	return answer;
}

int main()
{
//	freopen("input.txt", "r", stdin);
	
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i ++) {
		st[0].insert(i);
	}
	
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i);
		add(a[i]);
	}
	
	while(q --) {
		int i, j;
		scanf("%d %d", &i, &j);
		ers(a[i]);
		a[i] = j;
		add(a[i]);
		printf("%d\n", solve());
	}
	
	return 0;
}
