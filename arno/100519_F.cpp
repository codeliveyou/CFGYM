#include<bits/stdc++.h>
using namespace std;
using DO = double;

int main(){
	DO xa, ya, xb, yb, xc, yc, d, v, w;
	int h1, m1, h2, m2;
	
	cin >> xa >> ya >> xb >> yb >> xc >> yc;
	scanf("%lf %lf", &d, &v);
	scanf("%d %*c %d %d %*c %d", &h1, &m1, &h2, &m2);
	scanf("%lf", &w);
	
	DO ab, ac, bc;
	ab = hypot(xa - xb, ya - yb) * 1000;
	ac = hypot(xa - xc, ya - yc) * 1000;
	bc = hypot(xb - xc, yb - yc) * 1000;
	DO t1 = (ac + bc) / (v / 3.6) + d * 60;
	DO t2 = (h1 - 9 + h2) * 3600 + (m1 + m2) * 60;
	DO t3 = ab / (w / 3.6);
	if(fabs(ac + bc - ab) < 1e-8)
	{
		t3 += d * 60;
	}
	if(t1 < t2 && t1 < t3)
	{
		puts("Alex");
	}
	else if(t2 < t1 && t2 < t3)
	{
		puts("Dmitry");
	}
	else
	{
		puts("Petr");
	}
	return 0;
}
