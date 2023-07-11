#include "bits/stdc++.h"

using namespace std;
using VI = vector<int>;
const int N = 222;

int a[N];
int pre[11];
int cnt[11];
int n;

void rem(VI & v) {
	printf("- %d", (int) v.size());
	for(auto r : v) {
		printf(" %d", r);
	}
	puts("");
	fflush(stdout);
}

void get(int * x) {
	for(int i = 1; i < 10; i ++) {
		x[i] = 0;
	}
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i);
		x[a[i]] ++;
	}
}

int ano() {
	for(int i = 1; i < 10; i ++) {
		if(cnt[i] > pre[i]) {
			return i;
		}
	}
	return -1;
}

void solve() {
	cin >> n;
	get(cnt);
	int mimic;
	while(true) {
		VI tmp;
		rem(tmp);
		for(int i =1; i < 10; i ++) {
			pre[i] = cnt[i];
		}
		get(cnt);
		int typ = ano();
		if(typ != -1) {
			mimic = typ;
			break;
		}
	}
	VI tmp;
	for(int i = 1; i <= n; i ++) {
		if(a[i] != mimic) {
			tmp.push_back(i);
		}
	}
	
	rem(tmp);
	for(int i = 1; i < 10; i ++) {
		if(mimic != i) {
			pre[i] = 0;
		}
		else {
			pre[i] = cnt[i];
		}
	}
	
	n -= tmp.size();
	get(cnt);
	
//	for(int i = 1; i < 10; i ++) cout << pre[i] << ' '; cout << endl;
//	for(int i = 1; i < 10; i ++) cout << cnt[i] << ' '; cout << endl;
	
	if(cnt[mimic] < pre[mimic]) {
		for(int i = 1; i <= n; i ++) {
			if(a[i] != mimic) {
				printf("! %d\n", i);
				fflush(stdout);
				return;
			}
		}
	}
	
	for(int i = 1; i < 10; i ++) {
		pre[i] = cnt[i];
	}
	while(true) {
		VI tmp;
		rem(tmp);
		get(cnt);
		if(cnt[mimic] < pre[mimic]) {
			for(int i = 1; i <= n; i ++) {
				if(a[i] != mimic) {
					printf("! %d\n", i);
					fflush(stdout);
					return;
				}
			}
		}
		for(int i = 1; i < 10; i ++) {
			pre[i] = cnt[i];
		}
	}
}

int main() {
	int T; cin >> T;
	while(T --) {
		solve();
	}
}
