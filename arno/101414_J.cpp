#include <bits/stdc++.h>

using namespace std;

const int maxn=10;

const int dx[]={0,1,0,-1,1,-1,-1,1};
const int dy[]={1,0,-1,0,-1,-1,1,1};

struct mp
{
	int x,y,res;
	string a[maxn];
};

int n;
set<int> hashs;
bool ok;

inline bool hashes(mp x)
{
	int hsh=0,pow2=1,t=0;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++)
	{
		if(x.a[i][j]=='#') hsh+=pow2;
		if(x.a[i][j]=='@') t=i*n+j;
		pow2*=2;
	}
	hsh=hsh*26+t;
	
	if(hashs.count(hsh)) return 0; else {hashs.insert(hsh);return 1;}
}

inline void spread(mp &x)
{
	mp t=x;
	
	for(int i=0;i<n;i++) for(int j=0;j<n;j++)
	{
		int cnt=0;
		for(int k=0;k<8;k++)
		{
			int cx=i+dx[k],cy=j+dy[k];
			if(cx>=0&&cx<n&&cy>=0&&cy<n&&x.a[cx][cy]!='.') cnt++;
		}
		
		if(x.a[i][j]=='#')
		{
			if(cnt!=2&&cnt!=3) t.a[i][j]='.';
		}
		else if(x.a[i][j]=='.')
		{
			if(cnt==3) t.a[i][j]='#';
		}
	}
	
	x=t;
}

inline bool check(mp x)
{
	bool finish=1;
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(x.a[i][j]=='#') {finish=0;break;}
	return finish;
}

inline void bfs()
{
	ok=0;hashs.clear();
	queue<mp> q;while(!q.empty()) q.pop();
	
	mp IN;IN.res=0;
	for(int i=0;i<n;i++)
	{
		cin>>IN.a[i];
		for(int j=0;j<n;j++) if(IN.a[i][j]=='@') IN.x=i,IN.y=j;
	}
	
	if(check(IN))
	{
		ok=1;
		puts("0");
		return;
	}
	
	q.push(IN);
	hashes(IN);
	while(!q.empty())
	{
		mp X=q.front();q.pop();
		
		for(int i=0;i<8;i++)
		{
			mp x=X;
			int cx=x.x+dx[i],cy=x.y+dy[i];
			if(cx>=0&&cx<n&&cy>=0&&cy<n&&x.a[cx][cy]=='.')
			{
				x.a[x.x][x.y]='.';
				x.a[cx][cy]='@';
				x.x=cx;x.y=cy;
				x.res++;
				spread(x);
				
				if(hashes(x))
				{
					if(check(x))
					{
						ok=1;
						printf("%d\n",x.res);
						return;
					}
					q.push(x);
				}
			}
		}
	}
}

int main()
{
#ifdef ONLINE_JUDGE
freopen("J.in","r",stdin);
#endif
	
	while(scanf("%d",&n)&&n)
	{
		bfs();
		if(!ok) puts("-1");
	}
	
	return 0;
}
