#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct str { int size,mark; } dot[1010],dt[1010];

int peo[11][5],n,tp,top;
int A[1010],size[1010],sz[1010],ans;
int num[1010][1010];

bool cmp(const str &a, const str &b) {
	return (a.size < b.size);
}

void update_ans() {
	int k = 0;
	for (int i = 1; i <= top; i++)
		if (dot[i].size == 2) k++;
	if ((k + 1) / 2 + (top - k) > 9) return;
	int now = 0;
	for (int i = 1; i <= top; i++) {
		now += dot[i].size * (dot[i].size - 1) * A[dot[i].mark];
	}
	if (now > ans) {
		ans = now; tp = top;
		for (int i = 1; i <= top; i++) dt[i] = dot[i];
	}
}

void dfs(int u,int v) {
	if (u > n) { update_ans(); return; }  
	dfs(u + 1,0);
	for (int i = 2; i + v <= size[u]; i++) {
		dot[++top].mark = u; dot[top].size = i;
		dfs(u + (i + v) / size[u],(i + v) % size[u]);
		top--;
	}
}

void get_ans() {
	printf("%d\n",ans);
	for (int i = 1; i <= tp; i++) {
		for (int j = 1; j <= 9; j++) {
			if (sz[j] + dt[i].size <= 4) {
				for (int k = 1; k <= dt[i].size; k++) peo[j][++sz[j]] = num[dt[i].mark][size[dt[i].mark]--];
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 9; j++) {
			while (sz[j] < 4 && size[i]) {
				peo[j][++sz[j]] = num[i][size[i]--];
			}
		}
	}
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 4; j++) printf("%d ",peo[i][j]);
		putchar('\n');
	}
}

int main() {
	freopen("tickets.in","r",stdin);
	freopen("tickets.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d",&size[i],&A[i]);
		for (int j = 1; j <= size[i]; j++) scanf("%d",&num[i][j]);
	}
	dfs(1,0);
	get_ans();
	return 0;
}
