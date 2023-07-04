#include<bits/stdc++.h>

using namespace std;

const int max_n = 1e6 + 10;

char s[max_n];

bool ok(char s) {
	return s == '1' || s == '3' || s == '7' || s == '9';
}

int main() {
	
	int k;
	scanf("%s %d", s, &k);
	map<int, int> mp;
	
	int n = strlen(s);
	int current_value = 0;
	int pw = 1 % k;
	long long answer = 0;
	
	for(int i = n - 1; i >= 0; i --) {
		mp[current_value] += 1;
		current_value = (current_value + pw * (s[i] - '0')) % k;
		pw = (pw * 10) % k;
		if(mp.count(current_value)) {
			answer += mp[current_value];
		}
	}
	
	cout << answer << endl;
	
	return 0;
}
