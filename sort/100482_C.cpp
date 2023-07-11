#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

char s[N];
int bucket[26];

void Sort(int L, int R) {
	memset(bucket, 0, sizeof bucket);
	for(int i = L; i <= R; i ++) {
		bucket[s[i] - 'A'] ++;
	}
	for(int i = 0; i < 26; i ++) {
		while(bucket[i] --) {
			s[L ++] = 'A' + i;
		}
	}
}

int main() {
	freopen("output.txt", "w", stdout);
	int T; cin >> T;
	for(int tcase = 1; tcase <= T; tcase ++) {
		scanf("%s", s);
		int q;
		scanf("%d", &q);
		printf("Case #%d:\n", tcase);
		while(q --) {
			char typ;
			int l, r;
			scanf(" %c %d %d", &typ, &l, &r);
			if(typ == 'g') {
				memset(bucket, 0, sizeof bucket);
				for(int i = l; i <= r; i ++) {
					bucket[s[i] - 'A'] ++;
				}
				for (int i = 0; i < 26; i ++) {
					printf("%d%c", bucket[i], i == 25 ? '\n' : ' ');
				}
			}
			else {
				Sort(l, r);
			}
		}
	}
	return 0;
}
