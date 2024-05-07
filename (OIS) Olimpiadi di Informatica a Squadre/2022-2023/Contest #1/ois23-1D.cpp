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

const int INF = LLONG_MAX >> 2;

void solve() {
    int N, K; cin >> N >> K;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    
    Vec<2, int> cost(N, 37, -INF);
    for (int i = 0; i < N; ++i) {
        for (int r1 = 3; r1 <= 11; ++r1) chmax(cost[i][r1], A[(i+r1)%N]);
        for (int r1 = 2; r1 <= 12; r1 += 2) {
            for (int r2 = 3; r2 <= 11; ++r2) chmax(cost[i][r1+r2], A[(i+r1)%N] + A[(i+r1+r2)%N]);
        }
        for (int r1 = 2; r1 <= 12; r1 += 2) {
            for (int r2 = 2; r2 <= 12; r2 += 2) {
                for (int r3 = 2; r3 <= 12; ++r3) chmax(cost[i][r1+r2+r3], A[(i+r1)%N] + A[(i+r1+r2)%N] + A[(i+r1+r2+r3)%N]);
            }
        }
    }
    
    // for (int i = 3; i <= 36; ++i) debug(i, cost[0][i]);
    
    Vec<2, int> dp(K+1, N, -INF); dp[0][0] = 0;
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int s = 3; s <= 36; ++s) chmax(dp[i+1][(j+s)%N], dp[i][j] + cost[j][s]);
        }
    }
    cout << *max_element(ALL(dp[K])) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
