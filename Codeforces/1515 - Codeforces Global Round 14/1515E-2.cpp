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
#define ef push_front
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N, mod; cin >> N >> mod;
    
    vector<vector<int>> dp(4, vector<int>(N+2, 0));
    const int now = 3;
    dp[now][0] = 1;
    for (int i = 1; i <= N; ++i) {
        swap(dp[0], dp[1]), swap(dp[1], dp[2]), swap(dp[2], dp[3]);
        fill(ALL(dp[now]), 0);
        for (int a = 1; a <= N; ++a) {
            dp[now][a] = (dp[now-1][a] * 2 * a % mod
                        + dp[now-2][a] * 2 * a % mod
                        + dp[now-1][a-1] * a % mod
                        + dp[now-2][a+1] * 2 * a % mod
                        + dp[now-3][a+1] * a % mod) % mod;
        }
        // for (int j = 1; j <= N; ++j) cout << dp[now][j] << " \n"[j == N];
    }
    cout << dp[now][1] << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
