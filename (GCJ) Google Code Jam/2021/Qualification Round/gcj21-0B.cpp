#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int INF = INT_MAX;

void solve() {
    int A, B, n;
    string s;
    cin >> A >> B >> s, n = s.size();
    
    int dp[n][2];
    memset(dp, 0x00, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        if (i) dp[i][0] = min(dp[i-1][0], dp[i-1][1] + B);
        if (i) dp[i][1] = min(dp[i-1][1], dp[i-1][0] + A);
        if (s[i] == 'C') dp[i][1] = INF;
        if (s[i] == 'J') dp[i][0] = INF;
    }
    cout << min(dp[n-1][0], dp[n-1][1]) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}