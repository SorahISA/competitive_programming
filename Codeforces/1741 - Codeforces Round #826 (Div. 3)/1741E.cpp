#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    
    vector<int> dp(N+1, 0); dp[0] = 1;
    for (int i = 0; i <= N; ++i) {
        if (i >= 1 and i - A[i-1] - 1 >= 0) dp[i] |= dp[i - A[i-1] - 1];
        if (i < N and i + A[i] + 1 <= N) dp[i + A[i] + 1] |= dp[i];
    }
    cout << (dp[N] ? "Yes" : "No") << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
