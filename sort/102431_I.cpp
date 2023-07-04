#include "bits/stdc++.h"

using namespace std;
 
int main() {
    int T; cin >> T;
    for(int cas = 1; cas <= T; cas ++) {
    	int n; cin >> n;
    	printf("Case #%d:\nYES\n", cas);
    	for(int i = 1; i <= n; i ++) {
    		for(int j = i; j <= n; j ++) {
    			printf("%d %d %d %d %d %d %d %d\n", i, j, i, j, 1, i, j, 2);
    		}
    	}
    }
    return 0;
}
