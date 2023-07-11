#include <bits/stdc++.h>
using namespace std;

const int N = 555;

int n, cnt, x, y, tmpx, tmpy;
char a[N][N];

void handle(int i, int j) {
	for (tmpx = i, tmpy = j; tmpx < n && (a[tmpx][tmpy] == '+' || a[tmpx][tmpy] == '|'); tmpx++);
	if (a[tmpx][tmpy] == 'O') {
		cnt++;
		x = tmpx;
		y = tmpy;
	}
	
	for (tmpx = i, tmpy = j; tmpx > 1 && (a[tmpx][tmpy] == '+' || a[tmpx][tmpy] == '|'); tmpx--);
	if (a[tmpx][tmpy] == 'O') {
		cnt++;
		x = tmpx;
		y = tmpy;
	}
	for (tmpx = i, tmpy = j; tmpy < n && (a[tmpx][tmpy] == '+' || a[tmpx][tmpy] == '-'); tmpy++);
	if (a[tmpx][tmpy] == 'O') {
		cnt++;
		x = tmpx;
		y = tmpy;
	}
	for (tmpx = i, tmpy = j; tmpy > 1 && (a[tmpx][tmpy] == '+' || a[tmpx][tmpy] == '-'); tmpy--);
	if (a[tmpx][tmpy] == 'O') {
		cnt++;
		x = tmpx;
		y = tmpy;
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == '+') {
				cnt = 0;
				handle(i, j);
				if (cnt == 0) {
					puts("No");
					return 0;
				}
			}
		}
	}
	for (int k = 1; k <= 7; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (a[i][j] == '+') {
					cnt = 0;
					x = y = -1;
					handle(i, j);
					if (cnt == 1) {
						int tmpx = i, tmpy = j;
						while (tmpx < x && a[tmpx][tmpy] == '+') {
							a[tmpx][tmpy] = '|';
							tmpx++;
						}
						while (tmpx > x && a[tmpx][tmpy] == '+') {
							a[tmpx][tmpy] = '|';
							tmpx--;
						}
						while (tmpy < y && a[tmpx][tmpy] == '+') {
							a[tmpx][tmpy] = '-';
							tmpy++;
						}
						while (tmpy > y && a[tmpx][tmpy] == '+') {
							a[tmpx][tmpy] = '-';
							tmpy--;
						}
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == '+') {
				a[i][j] = '|';
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == '|' || a[i][j] == '-') {
				cnt = 0;
				handle(i, j);
				if (cnt == 0) {
					puts("No");
					return 0;
				}
			}
		}
	}
	puts("Yes");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			putchar(a[i][j]);
		}
		puts("");
	}
	return 0;
}
