#include "bits/stdc++.h"

using namespace std;

struct trie {
    int leaf;
    trie* child[2];
    trie() {
    	leaf = 0;
    }
};

inline trie* create() {
    trie* temp=new trie();
    memset(temp->child, 0, sizeof temp->child);
    return temp;
}

inline void add(trie* root, vector<bool> & s) {
    for(int i = 0; i < s.size(); i ++) {
        if(root->child[s[i]]==NULL)
            root->child[s[i]]=create();
        root=root->child[s[i]];
    }
    root->leaf += 1;
}

inline int count(trie* root, vector<bool> & s) {
	for(int i = 0; i < s.size(); i ++) {
        if(root->child[s[i]]==NULL) {
        	return 0;
        }
        root=root->child[s[i]];
    }
    return root->leaf;
}

trie* root;

const int M = 3e6 + 10;
char tmp[M];
vector<bool> a[M], b, x;
int bit[32];

inline void input(vector<bool> & v) {
    scanf("%s", tmp);
    for(int i = 0, b; tmp[i]; i ++) {
        b = (tmp[i] <= '9') ? (tmp[i] - '0') : (tmp[i] - 'A' + 10);
        for(int j = 4; j >= 0; j --) {
            if(b & bit[j]) {
                v.push_back(1);
            }
            else {
                v.push_back(0);
            }
        }
    }
    reverse(v.begin(), v.end());
    while(v.size() > 1 && v.back() == 0) {
        v.pop_back();
    }
}

int main() {
	root = create();
	
	for(int i = 0; i < 32; i ++) {
		bit[i] = 1 << i;
	}
    int n; scanf("%d", &n);
    input(x);
    for(int i = 0; i < n; i ++) {
        input(a[i]);
        add(root, a[i]);
    }
    
    if(x.back() == 0) {
    	long long answer = 0;
    	for(int i = 0; i < n; i ++) {
    		int t = count(root, a[i]);
			answer += 1ll * t * t;
    	}
    	answer -= n;
    	answer /= 2;
    	cout << answer << endl;
    	return 0;
    }
    
	long long answer = 0;
	
	for(int i = 0; i < n; i ++) {
		if(a[i].size() < x.size()) {
			continue;
		}
		b = a[i];
		for(int i = 0; i < x.size(); i ++) {
			b[i] = b[i] ^ x[i];
		}
		while(b.size() > 1 && b.back() == 0) {
			b.pop_back();
		}
		if(a[i].size() == x.size()) {
			answer += 2 * count(root, b);
		}
		else if(a[i].size() > x.size()) {
			answer += count(root, b);
		}
	}
	
	cout << answer / 2 << endl;

	return 0;
}

