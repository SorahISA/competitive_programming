#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = INT_MAX;

inline int MOD(int x, int mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

void solve() {
    int N; cin >> N;
    
    vector<vector<int>> dp(N+1, vector<int>(100, -INF));
    dp[0][0] = 0;
    for (int i = 1; i <= N; ++i) {
        int p, u; cin >> p >> u;
        for (int j = 0; j < 100; ++j) {
            chmax(dp[i][j], dp[i-1][j]);
            chmax(dp[i][j], dp[i-1][MOD(j - p, 100)] + u - p + (p / 100 + (j < p % 100)) * 20);
        }
    }
    cout << *max_element(ALL(dp[N])) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
