#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ee emplace
#define eb emplace_back
#define ef push_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    cerr << "\u001b[33m" << "At func " << __FUNCTION__ << ", line " << __LINE__ << ": ",\
    cerr << "(" << #__VA_ARGS__ << ") = ",\
    _do(__VA_ARGS__),\
    cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const double INF = 1e18;

void solve() {
    int N, K; cin >> N >> K;
    
    vector<pii> AB(N);
    for (auto &[A, B] : AB) cin >> A >> B, B = B == -1 ? (int)INF : B;
    sort(ALL(AB), [](pii &a, pii &b) {return a.Y < b.Y;});
    
    // for (auto &[A, B] : AB) debug(A, B);
    
    vector<vector<int>> suf_min_k(N+1, vector<int>(K+1, 0));
    for (int i = N-1; i >= 0; --i) {
        vector<pii> tmp(i + ALL(AB));
        sort(ALL(tmp));
        for (int j = 0; j < min(SZ(tmp), K); ++j) suf_min_k[i][j+1] = tmp[j].X;
        partial_sum(ALL(suf_min_k[i]), begin(suf_min_k[i]));
    }
    
    double min_time = suf_min_k[0][K]; /// goal = 0
    for (int goal = 1; goal <= K; ++goal) {
        vector<vector<double>> dp(N, vector<double>(goal+1, INF));
        dp[0][0] = (double)AB[0].X / (goal+1), dp[0][1] = AB[0].Y;
        for (int i = 1; i < N; ++i) {
            for (int j = goal; j >= 0; --j) {
                chmin(dp[i][j], dp[i-1][j] + (double)AB[i].X / (goal+1));
                if (j) chmin(dp[i][j], dp[i-1][j-1] + (double)AB[i].Y / j);
            }
        }
        for (int i = goal; i <= K; ++i) {
            chmin(min_time, dp[i-1][goal] + (double)suf_min_k[i][K-i] / (goal+1));
        }
    }
    cout << fixed << setprecision(12) << min_time << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
