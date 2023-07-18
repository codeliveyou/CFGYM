#include<bits/stdc++.h>

using namespace std;
long long p[10010],s[10010],S[10010];
long long A[110],ans[110];
int al;

int cmp(const void *xx,const void *yy)
{
	long long x=*(long long *)xx, y=*(long long *)yy;
	if(x<y)return -1;
	return 1;
}

int main()
{
	int T,n,i,j,x,y,o=0,t;
	long long sum;
	scanf("%d",&T);
	while(T--)
	{
	  scanf("%d",&n);
	  for(i=1;i<=n;i++)
	  {
	    scanf("%I64d",&p[i]);
	    if(!p[i])t=i;
	  }
	  sum=0;
	  for(i=1;i<=n;i++)
	  {
	    scanf("%I64d",&s[i]);
		S[i]=s[i];
	    sum+=s[i];
	  }
	  al=0;
	  while(sum>>=1)
	  {
		for(x=1;x<=n;x++)
		  if(s[x])break;
	    if(s[x]>1)
		{
		  A[++al]=0;
		  for(i=1;i<=n;i++)s[i]>>=1;
		}
		else
		{
		  for(y=x+1;y<=n;y++)
			if(s[y])break;
		  A[++al]=p[y]-p[x];
		  for(i=x;i<=n;i++)
		    if(s[i])
			{
			  while(p[y]-p[i]!=A[al])y++;
			  s[y]-=s[i];
  		    }
		}
	  }
	  for(i=1;i<=n;i++)s[i]=S[i];
	  for(i=al;i>=1;i--)
	  {
		if(!A[i]){ans[i]=0;continue;}
		for(x=n;x>=1;x--)
		  if(s[x])break;
	    y=x;
	    for(j=x;j>=1;j--)
		  if(s[j])
		  {
			while(p[j]-p[y]!=A[i])y--;
			s[y]-=s[j];
		  }
	    if(s[t])ans[i]=-A[i];
		else
		{
		  ans[i]=A[i];
		  x=1;
		  for(j=1;j<=n;j++)
			if(s[j])
			{
			  while(p[j]-p[x]!=A[i])x++;
			  s[x]=s[j];s[j]=0;
			}
		}
	  }
	  qsort(ans+1,al,sizeof(long long),cmp);
	  printf("Case #%d:",++o);
	  for(i=1;i<=al;i++)printf(" %I64d",ans[i]);
	  printf("\n");
	}
	return 0;
}
