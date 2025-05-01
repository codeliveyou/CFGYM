#include <bits/stdc++.h>
using namespace std;

int main() 
{
    int T; cin >> T;
    while(T --) {
      int n, x; scanf("%d %d", &n, &x);
      if(n == 1) {
        if(x == 0) x = -1;
        cout << x << endl;
      }
      else {
        int k = __builtin_popcount(x);
        if(k >= n) {
          cout << x << endl;
        }
        else {
          if(k == 0) {
            if(n & 1) {
              cout << n - 1 + 4 << endl;
            }
            else {
              cout << n << endl;
            }
          }
          else if(k == 1) {
            if(x == 1) {
              if(n & 1) {
                cout << n << endl;
              }
              else {
                if(n == 1) {
                  cout << n << endl;
                }
                else {
                  cout << 1 + 2 + 2 + (n - 2) << endl;
                }
              }
            }
            else {
              cout << x + (n / 2) * 2 << endl;
            }
          }
          else {
            cout << x + (n - k + 1) / 2 * 2 << endl;
          }
        }
      }
    }
}