#include<bits/stdc++.h>

using namespace std;
size_t n,m;
vector<int> seq[128];
bool mark[128];
string front[128],back[128];
set<string> ans;
void add(const string& s){
	for(size_t i=0;i+m<=s.length();++i)
		ans.insert(s.substr(i,m));
}
void dfs(int k){
	if(mark[k])return;
	mark[k]  = true;
	if(!seq[k].size()){
		add(front[k] = string(1,k+48));
		return;
	}
	string tmp;
	for(size_t i=0;i<seq[k].size();++i){
		int c = seq[k][i];
		dfs(c);
		tmp+= front[c];
		if(back[c].size()){
			add(tmp);
			if(!front[k].size())front[k] = tmp.substr(0,m-1);
			tmp = back[c];
		}
	}
	add(tmp);
	if(!front[k].size()){
		if(tmp.size()<m){
			front[k] = tmp;
			return;
		}
		else front[k] = tmp.substr(0,m-1);
	}
	if(tmp.size()>=m-1)
		back[k] = tmp.substr(tmp.size()-m+1);
}
int main(){
	cin >> n >> m;
	for(int i=1,t;i<=n;++i){
		cin >> t;
		if(t==-1)t=0;
		seq[i] .resize(t);
		for(int j=0;j<t;++j)cin >> seq[i][j];
		mark[i] = false;
	}
	for(int i=1;i<=n;++i)
		dfs(i);
	cout << ans.size() << endl;
}
