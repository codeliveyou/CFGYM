#include <bits/stdc++.h>
using namespace std;

const int N = 3e4 + 10, more = 222;

int frequency[N], count_of_frequency[N];
int a[N], ans[N];
int uni[N];

struct node{
	int L, R, id;
	node(){};
	bool operator < (const node & a) {
		return L / more != R / more ? L < a.L : R < a.R;
	}
	void input(int i) {
		id = i;
		scanf("%d %d", &L, &R);
		L --; R --;
	}
} q[N];


void add_tempreture(int L){
	count_of_frequency[min(more, frequency[L])]--;
	frequency[L]++;
	count_of_frequency[min(more, frequency[L])]++;
}

void delete_tempreture(int L){
	count_of_frequency[min(more, frequency[L])]--;
	frequency[L]--;
	count_of_frequency[min(more, frequency[L])]++;
}

int main(){
	int n, m, k = 0;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i ++){
		cin >> a[i];
		uni[k ++] = a[i];
	}
	sort(uni, uni + k);
	k = unique(uni, uni + k) - uni;
	for(int i = 0; i < n; i ++) {
		a[i] = lower_bound(uni, uni + k, a[i]) - uni;
	}
	for(int i = 0; i < m; i ++) {
		q[i].input(i);
	}
	sort(q, q + m);
	count_of_frequency[0] += k;
	for(int i = 0, L = 0, R = 0; i < m; i ++) {
		while(R <= q[i].R) add_tempreture(a[R ++]);
		while(L > q[i].L) add_tempreture(a[-- L]);
		while(R > q[i].R + 1) delete_tempreture(a[-- R]);
		while(L < q[i].L) delete_tempreture(a[L ++]);
		for(int quality = more, s = 0; quality; quality --) {
			s += count_of_frequency[quality];
			if(s >= quality) {
				ans[q[i].id] = quality;
				break;
			}
		}
	}
	for(int i = 0; i < m; i ++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
