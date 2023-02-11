#include <bits/stdc++.h>
using namespace std;

#define int int64_t

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = LLONG_MAX >> 2;

void solve() {
    int N, K; cin >> N >> K;
    
    vector<int> H(N+2);
    for (int i = 1; i <= N; ++i) cin >> H[i];
    H[N+1] = 0;
    
    vector<vector<int>> dp(N+2, vector<int>(N+1, INF));
    dp[0][0] = 0;
    
    for (int i = 1; i <= N+1; ++i) {
        for (int j = i-1; j >= 0; --j) {
            for (int k = i-j-1, l = 0; k <= i; ++k, ++l) {
                chmin(dp[i][k], dp[j][l] + max(H[i] - H[j], (int)0));
            }
        }
    }
    cout << dp[N+1][K] << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
