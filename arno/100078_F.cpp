#include <stack>
#include <cstdio>
#include <vector>
#include <string>
#include <math.h>
#include <cctype>
#include <bitset>
#include <cstring>
#include <numeric>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;
const int N = 11;
typedef bitset< 1<<N > formula;

formula v[N],result;
char s[1024];
int n;
int parenthese[1024];
formula gao(int l,int r){
	if(l+1==r && islower(s[l]))
		return v[s[l]-'a'];
	int h1=-1,h2=-1;
	for(int i=l;i<r;++i){
		if(s[i]=='|'){h1=i;break;}
		if(s[i]=='&' && h2==-1)h2=i;
		if(s[i]=='(')i=parenthese[i];		
	}
	if(~h1)
		return gao(l,h1) | gao(h1+1,r);
	if(~h2)
		return gao(l,h2) & gao(h2+1,r);
	int negc = 0;
	for(;s[l] =='~';++negc) l++;
	for(;s[l] == '(' && parenthese[l] == r-1; l++,r--);
	return (negc&1)?~gao(l,r):gao(l,r);
}
string gao(int all,const formula& f,bool pos=true){
	if(__builtin_popcount(all)==1)
		return (f[all]?"":"~")+string(1,'a'+__builtin_ctz(all));
	for(int x = all -1 &all;x;x= x-1 & all){
		int y = all&~x;
		if(x<y)break;
		formula fx,fy;
		bool ok = true;
		for(int h=all;;h=h-1&all){
			if(f[h])fx[h&x] = fy[h&y] = 1;
			// nx[h&x] = ny [h&y] =1
			if(!h)break;
		}
		for(int h = all;ok;h=h-1&all){
			if(ok && f[h]!=fx[x&h]&&fy[y&h])ok =false;
			if(!h)break;
		}
		if(ok)return "("+gao(y,fy)+ ")&("+gao(x,fx)+")";
	}
	if(pos )return "~("+gao(all, ~f,false)+")";
	throw 0;
}
int main(){
#ifdef ONLINE_JUDGE
	freopen("formula.in","r",stdin);
	freopen("formula.out","w",stdout);
#endif
	gets(s);
	n = 'a';
	int l = 0;
	for(char *p = s;*p;++p)
	if(!isspace(*p))s[l++] = *p;
	s[l] = '\0';
	for(char *p = s;*p;++p)
	if(islower(*p)){
			n = max(n,(int) *p);
		}
	n = n-'a'+1;
	for(int i=0;i<n;++i)
		for(int j=0;j<1<<n;++j)
			if(j&1<<i)v[i].set(j);
	{	stack<int> tmp;
		for(int i=0;i<l;++i){
			if(s[i]=='(')tmp.push(i);
			if(s[i]==')'){
				parenthese[tmp.top()] = i;
				tmp.pop();
			}
		}
		assert(tmp.size()==0);
	}
	result = gao(0,l);
	int needed =0;
	for(int i=0;i<1<<n;++i){
		for(int j=0;j<n;++j){
			
		}
	}
	for(int i=0;i<n;++i)
		for(int j=0;j<1<<n;++j)
		if(result[j] ^ result[j^1<<i]){
			needed |= 1<<i;
			break;
		}
	if(needed == 0)return puts("No")&0;
	try{
		string ans = gao(needed,result);
		puts("Yes");
		puts(ans.c_str());
	}
	catch (...){
		puts("No");
	}
}
