#include <bits/stdc++.h>
using namespace std;

#define int long long

#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int N; cin >> N;
    
    int ans = 0;
    for (int i = 1; i*i <= N; ++i) {
        ans += N / i;
        if (i != N / i) ans += i * (N / i - N / (i+1));
        // cerr << "add " << (N / i - N / (i+1)) << " amounts of " << i << "\n";
    }
    cout << ans % 1'000'000 << "\n";
    
    // int chk = 0;
    // for (int i = 1; i <= N; ++i) chk += N / i;
    // cerr << chk << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
