#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    template <typename ...U> Vec(int n = 0, U ..._u) :
        vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};

template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T &val = T()) :
        vector<T>(n, val) {}
};

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << endl;}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#define endl "\n"
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int mod = 1E9 + 7;

void solve() {
    int N, M; cin >> N >> M;
    
    Vec<2, int> A(M+1, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= M; ++j) cin >> A[j][i];
    }
    
    
    Vec<2, int> dp(M+1, 1<<N, 0); dp[0][0] = 1;
    Vec<2, int> mx(M+1, 1<<N, 0);
    for (int i = 1; i <= M; ++i) {
        for (int j = 0; j < (1<<N); ++j) {
            dp[i][j] = dp[i-1][j];
            mx[i][j] = mx[i-1][j];
            for (int k = 0; k < N; ++k) {
                if (j >> k & 1 and A[i][k]) {
                    dp[i][j] += dp[i-1][j^(1<<k)];
                    chmax(mx[i][j], mx[i-1][j^(1<<k)] + 1);
                }
            }
            dp[i][j] %= mod;
            // debug(i, bitset<4>(j).to_string(), dp[i][j]);
        }
    }
    
    int ans = 0;
    for (int i = 0; i < (1<<N); ++i) {
        if (__builtin_popcount(i) == mx[M].back()) ans += dp[M][i];
    }
    cout << ans % mod << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
