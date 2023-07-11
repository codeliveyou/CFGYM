#include <bits/stdc++.h>
using namespace std;
const int LIM = 5e4+10;
int dpm[LIM+1];
bool back[2][LIM+1];

int main() {
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n;
	int m;
	int ans = 0;
	int type;
	int dif;
	int in;
	int state;

	fill(dpm, dpm+LIM+1, 1);

	for(int i = 1; i*i <= LIM; i++) {
		for(int j = 1; ; j++) {
			if(2*i + j > LIM) break;
			for(int k = 2; ; k++) {
				state = k*i + k*(k-1)/2*j;
				if(state > LIM) break;
				dpm[state] = max(dpm[state], k);
			}
		}
	}

	cin >> n;

	fill(back[0], back[0]+LIM+1, false);
	back[0][1] = true;

	while(n--) {
		fill(back[1], back[1]+LIM+1, false);
		cin >> type >> m;

		while(m--) {
			cin >> in;
			dif = (3-2*type)*in;
			for(int j = 0; j <= LIM; j++) {
				if(j-dif <= 0 || j-dif > LIM) continue;
				back[1][j] |= back[0][j-dif];
			}
		}
		memcpy(back[0], back[1], LIM+1);
	}

	for(int i = 1; i <= LIM; i++)
		if(back[0][i])
			ans = max(ans, dpm[i]);

	cout << ans << '\n';
}
