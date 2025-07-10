#include <bits/stdc++.h>
using namespace std;

int64_t mod;

int main() {
    
    int N; cin >> N >> mod;
    
    int64_t ans = 1;
    for (int64_t i = 1; i <= N; ++i) {
        if (i & 1) ans = (ans * i - 1 + mod) % mod;
        else       ans = (ans * i + 1)       % mod;
        cout << ans << " \n"[i == N];
    }
    
    return 0;
}
