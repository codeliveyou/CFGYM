#include <iostream>
using namespace std;

int main() 
{
    int T; cin >> T;
    while(T --) {
      int n; scanf("%d", &n);
      cout << (n / 2) * (n - n / 2) + 1 << endl;
    }
}