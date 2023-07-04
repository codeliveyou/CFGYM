#include<bits/stdc++.h>

using namespace std;
using LL = long long;

struct seg {
	LL st, ed, d;
	seg(LL st = 0, LL ed = 0, LL d = 0) : st(st), ed(ed), d(d) {}
	
};

const int N = 3e5 + 10;
LL a[N];

vector<seg> complete(vector<seg> t, seg s) {
	if(t.empty()) {
		t.push_back(s);
		return t;
	}
	
	seg last = t.back();
	t.pop_back();
	
	// s is large
	if(last.ed < s.d) {
		t.push_back(last);
		t.push_back(s);
		return t;
	}
	
	// |s| is divisible by |t|
	if(s.d % last.d == 0) {
		last.ed = s.ed;
		t.push_back(last);
		return t;
	}
	
	// |t| > |s|
	if(last.d > s.d) {
		if(last.d % s.d == 0) {
			last.ed = s.ed;
			last.d = s.d;
			t = complete(t, last);
		}
		else {
			LL rem = last.d % s.d;
			if(rem + s.d > t.back().ed) {
				t = complete(t, seg(last.st, last.st + rem, rem));
				t = complete(t, seg(last.st + rem, s.ed, s.d));
			}
			else {
				last.ed = s.ed;
				last.d = __gcd(last.d, s.d);
				t = complete(t, last);
			}
		}
		return t;
	}
	
	if(s.d == s.st) {
		t.push_back(last);
		t.push_back(s);
		return t;
	}
	
	// last is large
	if(last.d * 2 > last.ed) {
		vector<seg> tmp;
		for(int i = 0; i < t.size(); i ++) {
			if(s.st - s.d < t[i].ed) {
				if(((s.st - s.d) - t[i].st) % t[i].d == 0) {
					t.push_back(last);
					t.push_back(s);
					return t;
				}
				else {
					LL rem = (s.st - s.d - t[i].st) % t[i].d;
					if(s.st - s.d - t[i].st > t[i].d) {
						tmp.push_back(seg(t[i].st, s.st - s.d - rem, t[i].d));
					}
					tmp = complete(tmp, seg(s.st - s.d - rem, s.st - s.d, rem));
					tmp = complete(tmp, seg(s.st - s.d, s.st - s.d + t[i].d - rem, t[i].d - rem));
					if(s.st - s.d + t[i].d - rem < t[i].ed) {
						tmp = complete(tmp, seg(s.st - s.d + t[i].d - rem, t[i].ed, t[i].d));
					}
					for(int j = i + 1; j < t.size(); j ++) {
						tmp = complete(tmp, t[j]);
					}
					tmp = complete(tmp, last);
					tmp = complete(tmp, s);
					return tmp;
				}
			}
			else {
				tmp.push_back(t[i]);
			}
		}
	}
	else {
		last.d = __gcd(last.d, s.d);
		last.ed = s.ed;
		t = complete(t, last);
	}
	return t;
}

LL solve(int n, LL L) {
	bool one = false;
	for(int i = 1; i <= n; i ++) {
		scanf("%I64d", a + i);
		if(a[i] == 1) {
			one = true;
		}
	}
	a[n + 1] = 1;
	n ++;
	sort(a + 1, a + n + 1);
	vector<seg> s;
	s.push_back(seg(0, 1, 1));
	for(int i = 2; i <= n; i ++) {
		s = complete(s, seg(a[i - 1], a[i], a[i] - a[i - 1]));
	}
	LL answer = 0;
	for(int i = 0; i < s.size(); i ++) {
		answer += (s[i].ed - s[i].st) / s[i].d;
	}
	return answer;
}

int main() {
	int n; LL L;
	while(true) {
		scanf("%d %I64d", &n, &L);
		if(n == 0) {
			break;
		}
		printf("%I64d\n", solve(n, L));
	}
	return 0;
}
