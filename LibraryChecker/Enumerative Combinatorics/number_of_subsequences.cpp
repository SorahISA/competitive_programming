#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int mod = 998'244'353;

void solve() {
    int N; cin >> N;
    
    map<int, int> app;
    vector<int> A(N+1), lst(N+1, -1);
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        if (app.contains(A[i])) lst[i] = app[A[i]];
        app[A[i]] = i;
    }
    
    vector<int> dp(N+1, 0); dp[0] = 1;
    for (int i = 1; i <= N; ++i) {
        dp[i] = (2 * dp[i-1] + (lst[i] == -1 ? 0 : mod - dp[lst[i] - 1])) % mod;
    }
    cout << (dp[N] + mod - 1) % mod << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
