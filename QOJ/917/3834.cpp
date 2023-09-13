#include <bits/stdc++.h>
using namespace std;

#ifdef local
#define fastIO() void()
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

void solve() {
    int N; cin >> N;
    
    vector<int> A(N), B(N);
    for (int &x : A) cin >> x;
    for (int &x : B) cin >> x;
    
    int ans = 0;
    for (int i = 0; i < N; ++i) ans += A[i] != B[i];
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
