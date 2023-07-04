#include "bits/stdc++.h"

using namespace std;

struct node
{
	int l, r, i;
	node(int l = 0, int r = 0, int i = 0) : l(l), r(r), i(i) {}
	bool operator < (const node & x) const
	{
		return r > x.r;
	}
};

const int N = 1e5 + 10, inf = 1e9;

priority_queue<node> leftSegments, moreWays;
int a[N], b[N], ans[N];
pair<int, int> pos[N];
node sem[N];

int main()
{
	int n, askShiftman = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i)
	{
		int x;
		scanf("%d", &x);
		pos[i] = {x, i};
	}
	sort(pos + 1, pos + n + 1);
	pos[0].first = 0;
	pos[n + 1].first = inf;
	for (int i = 0; i < n + 2; ++ i)
	{
		a[i] = pos[i].first;
		b[n + 1 - i] = inf - pos[i].first;
	}
	for (int i = 1, l, r; i <= n; ++ i)
	{
		scanf("%d %d", &l, &r);
		int sl = lower_bound(a, a + n + 2, l) - a;
		int sr = n + 1 - (lower_bound(b , b + n + 2, inf - r) - b);
		sem[i] = node(sl, sr, i);
	}
	sort(sem + 1, sem + n + 1, [](const node & x, const node & y)
	{
		return x.l < y.l;
	});
	for (int i = 1, j = 1; i <= n; ++ i)
	{
		while(j <= n && sem[j].l <= i)
		{
			leftSegments.push(sem[j ++]);
		}
		if (leftSegments.empty())
		{
			puts("Let's search for another office.");
			return 0;
		}
		node currentNode = leftSegments.top();
		leftSegments.pop();
		if (currentNode.r < i)
		{
			puts("Let's search for another office.");
			return 0;
		}
		ans[currentNode.i] = pos[i].second;
		while (!moreWays.empty())
		{
			node t = moreWays.top();
			if (t.l < i)
			{
				moreWays.pop();
				continue;
			}
			if (currentNode.l <= n - t.r)
			{
				askShiftman = 1;
			}
			break;
		}
		moreWays.push(node(currentNode.r, n - i, 0));
	}
	if (askShiftman)
	{
		puts("Ask Shiftman for help.");
		return 0;
	}
	puts("Perfect!");
	for (int i = 1; i <= n; ++ i)
	{
		printf("%d%c", ans[i], i == n ? '\n' : ' ');
	}
	return 0;
}
