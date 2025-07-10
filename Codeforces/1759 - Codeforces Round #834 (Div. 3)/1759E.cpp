#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

void solve() {
    i64 N, H; cin >> N >> H;
    
    vector<i64> A(N);
    for (i64 &x : A) cin >> x;
    sort(begin(A), end(A));
    
    vector dp(N+1, vector(3, vector<i64>(2, H)));
    for (int i = 0; i <= N; ++i) {
        for (int g : {2, 1, 0}) for (int b : {1, 0}) {
            if (i < N) dp[i+1][g][b] = max(dp[i+1][g][b], dp[i][g][b] + (dp[i][g][b] > A[i] ? A[i] / 2 : 0));
            if (g > 0) dp[i][g-1][b] = max(dp[i][g-1][b], dp[i][g][b] * 2);
            if (b > 0) dp[i][g][b-1] = max(dp[i][g][b-1], dp[i][g][b] * 3);
        }
    }
    
    int can_eat = count_if(begin(A), end(A), [&](i64 x) { return (x < dp[N][0][0]); });
    cout << can_eat << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
